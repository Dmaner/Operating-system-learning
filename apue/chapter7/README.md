## <font face="Consolas">Exercise 7.1</font>
> <font face="楷体">因为main函数返回为void故返回的是printf的返回值13（13个字符）</font>

## <font face="Consolas">Exercise 7.2</font>
> <font face="楷体">printf绑定到标准输出是行缓冲的，所以遇到换行符就输出</font>

## <font face="Consolas">Exercise 7.3</font>
> <font face="楷体">无</font>

## <font face="Consolas">Exercise 7.4</font>
> <font face="楷体">当C程序解引用一个空指针出错时，执行该程序的进程将终止。可以利用这种方式终止进程</font>

## <font face="Consolas">Exercise 7.5</font>
```c++
typedef void Exitfunc(void)
int atexit(Exitfunc* fp)
```

## <font face="Consolas">Exercise 7.6</font>
> <font face="楷体">为0，但分配指针数组要看0值是否与表示空指针的值相等</font>

## <font face="Consolas">Exercise 7.7</font>
> <font face="楷体">堆栈是根据程序运行时的大小分配</font>

## <font face="Consolas">Exercise 7.8</font>
> <font face="楷体">可执行文件 a.out 包含了用于调试 core 文件的符号表信息，可用strip删除</font>

## <font face="Consolas">Exercise 7.9</font>
> <font face="楷体">标准I/O库占了大部分</font>

## <font face="Consolas">Exercise 7.10</font>
> <font face="楷体">num和val都在这个f1的作用域，下一个调用函数可能将占领这块存储区，导致出错</font>