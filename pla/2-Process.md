# 第二章·进程的调度
---

> 关键词: 进程的表示&进程调度

### 进程状态

![image](images/process-state.png)


### 进程数据结构

> Linux涉及进程都是围绕着`task_struct`结构建立

简化的task_struct代码 (2.6版)

```c
// <sched.h> 
struct task_struct { 
    /* -1表示不可运行，0表示可运行，>0表示停止 */
    volatile long state;
    void *stack; 
    atomic_t usage;
    /* 进程标志，下文定义 */ 
    unsigned long flags;
    unsigned long ptrace;
    /* 大内核锁深度 */ 
    int lock_depth;

    int prio, static_prio, normal_prio; 
    struct list_head run_list;
    const struct sched_class *sched_class; 
    struct sched_entity se;
    
    unsigned short ioprio;
    unsigned long policy; 
    cpumask_t cpus_allowed; 
    unsigned int time_slice;
#if defined(CONFIG_SCHEDSTATS) || define (CONFIG_TASK_DELAY_ACCT) 
    struct sched_info sched_info;
#endif 
    /* ptrace_list/ptrace_children链表是
     * ptrace能够看到的当前进程的子进程列表。
     */
    struct list_head tasks;
    struct list_head ptrace_children; 
    struct list_head ptrace_list; 
    struct mm_struct *mm, *active_mm;
    
    /* 进程状态 */
    struct linux_binfmt *binfmt; 
    long exit_state;
    int exit_code, exit_signal; 
    
    /* 在父进程终止时发送的信号 */
    int pdeath_signal; 
    unsigned int personality; 
    unsigned did_exec:1; 

    /* 全局ID */  
    pid_t pid; 
    /* 线程组PID */
    pid_t tgid;

    /////////////////////////////////// 
    /* 真正的父进程（在被调试的情况下） */
    struct task_struct *real_parent;
    /* 父进程 */  
    struct task_struct *parent;
    /* 子进程链表 */
    struct list_head children;
    /* 连接到父进程的子进程链表 */ 
    struct list_head sibling;
    /* 线程组组长 */
    struct task_struct *group_leader; 
    //////////////////////////////////

    /* PID与PID散列表的联系。*/
    struct pid_link pids[PIDTYPE_MAX]; 
    struct list_head thread_group;
    
    /* 用于vfork() */
    struct completion *vfork_done; 
    /* CLONE_CHILD_SETTID */
    int __user *set_child_tid; 
    /* CLONE_CHILD_CLEARTID */
    int __user *clear_child_tid;

    unsigned long rt_priority;
    cputime_t utime, stime, utimescaled, stimescaled; 
    
    /* 上下文切换计数 */
    unsigned long nvcsw, nivcsw; 
    
    /* 单调时间 */
    struct timespec start_time;
    
    /* 启动以来的时间 */
    struct timespec real_start_time;  
    
    /* 内存管理器失效和页交换信息，这个有一点争论。
     * 它既可以看作是特定于内存管理器的， 
     * 也可以看作是特定于线程的 */ 
    unsigned long min_flt, maj_flt;

    cputime_t it_prof_expires, it_virt_expires; 
    unsigned long long it_sched_expires; 
    struct list_head cpu_timers[3];
    
    /* 进程身份凭据 */
    uid_t uid,euid,suid,fsuid; 
    gid_t gid,egid,sgid,fsgid; 
    struct group_info *group_info;
    kernel_cap_t cap_effective, cap_inheritable, cap_permitted;
    
    unsigned keep_capabilities:1; 
    struct user_struct *user;
    /* 除去路径后的可执行文件名称 
     * -用[gs]et_task_comm访问（其中用task_lock()锁定它） 
     * -通常由flush_old_exec初始化 */
    char comm[TASK_COMM_LEN]; 
    
    /* 文件系统信息 */ 
    int link_count, total_link_count;
    
    /* ipc相关 */
    struct sysv_sem sysvsem;
    
    /* 当前进程特定于CPU的状态信息 */ 
    struct thread_struct thread;
    
    /* 文件系统信息 */ 
    struct fs_struct *fs;
    
    /* 打开文件信息 */ 
    struct files_struct *files;
    
    /* 命名空间 */
    struct nsproxy *nsproxy;
    
    /* 信号处理程序 */
    struct signal_struct *signal; 
    struct sighand_struct *sighand;
    sigset_t blocked, real_blocked; 
    sigset_t saved_sigmask; /* 用TIF_RESTORE_SIGMASK恢复 */ 
    struct sigpending pending;
    unsigned long sas_ss_sp; 
    size_t sas_ss_size;
    int (*notifier)(void *priv); 
    void *notifier_data; 
    sigset_t *notifier_mask;
#ifdef CONFIG_SECURITY 
    void *security;
#endif 
    /* 线程组跟踪 */
    u32 parent_exec_id; 
    u32 self_exec_id;
    
    /* 日志文件系统信息 */ 
    void *journal_info; 
    
    /* 虚拟内存状态 */
    struct reclaim_state *reclaim_state; 
    struct backing_dev_info *backing_dev_info; 
    struct io_context *io_context;
    unsigned long ptrace_message;
    
    /* 由ptrace使用。*/ 
    siginfo_t *last_siginfo; 
    ... 
}; 
```

线程ID

> 进程在该命名空间下的唯一标识

- 内核下pid结构

```c
struct pid
{
    refcount_t count;
    unsigned int level;
    spinlock_t lock;
    /* 使用此PID的任务列表 */
    struct hlist_head tasks[PIDTYPE_MAX];
    struct hlist_head inodes;
    /* wait queue for pidfd notifications */
    wait_queue_head_t wait_pidfd;
    struct rcu_head rcu;
    struct upid numbers[1];
};
```

- 命名空间下pid结构

```c
struct upid {
    /* 表示该命名空间下的ID值 */
    int nr;
    /* 指向命名空间 */
    struct pid_namespace *ns;
};
```

![图2](./images/PID-ns.png)

进程关系

![图3](./images/process-relationship.png)

### 进程相关系统调用

`fork`系列函数

- `fork :` 创建父进程的副本     
- `vfork`(因为fork目前实现了写时复制, 而且比fork块, 故很少使用了) 
- `clone :` 产生线程

上述三个函数都需要依靠核心函数`do_fork`函数实现(内核2.6版本)

`do_fork`实现
```shell
do_fork
|----> 复制父进程
|    |----> 检查标志
|    |----> dup_task_struct
|    |----> 检查资源限制
|    |----> 初始化task_struct结构
|    |----> sched_fork
|    |----> 复制/共享进程各个部分
|    |    |----> copy_semundo
|    |    |----> copy_files
|    |    |----> copy_fs
|    |    |----> copy_sighand
|    |    |----> copy_signal
|    |    |----> copy_mm
|    |    |----> copy_namespace
|    |    |----> copy_thread
|    |----> 设置进程关系等等
|----> 在父进程命名空间选择pid
|----> 初始化vfork的完成处理程序(在设置CLONE_VFORK)和ptrace标志
|----> wake_up_new_task函数唤醒子进程
|----> 是否设置了CLONE_VFORK标志位
|    |----> wait_for_completion
```

`exec`系列函数