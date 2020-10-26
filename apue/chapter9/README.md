## <font face="Consolas">Exercise 9.1</font>
> <font face="楷体">因为 init 是登录 shell 的父进程，当登录 shell 终止时它收到 SIGCHLD 信号量，所以 init 进程知道什么时候终端用户注销。网络登录没有包含 init ，在 utmp 和wtmp 文件中的登录项和相应的注销项是由一个处理登录并检测注销的进程写的</font>

## <font face="Consolas">Exercise 9.2</font>
> <font face="楷体">见exc-9-2.c</font>