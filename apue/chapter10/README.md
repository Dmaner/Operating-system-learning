## <font face="Consolas">Exercise 10.1</font>
> <font face="楷体">传递完一次信号就结束了</font>

## <font face="Consolas">Exercise 10.2</font>
> <font face="楷体">待写</font>

## <font face="Consolas">Exercise 10.3</font>
> <font face="楷体">待写</font>

## <font face="Consolas">Exercise 10.4</font>
> <font face="楷体">在第一次调用 alarm 和 setjmp 之间有一次竞争条件。如果进程在调用 alarm 和 setjmp 之间被内核阻塞了，闹钟时间超过后就调用信号处理程序，然后调用 longjmp 。但是由于没有调用过 setjmp ，所以没有设置 env_alrm 缓冲区。如果 longjmp 的跳转缓冲区没有被 setjmp 初始化，则说明 longjmp 的操作是未定义的</font>

## <font face="Consolas">Exercise 10.5</font>
> <font face="楷体">待做</font>

## <font face="Consolas">Exercise 10.6</font>
> <font face="楷体">待做</font>

## <font face="Consolas">Exercise 10.7</font>
> <font face="楷体">待做</font>

## <font face="Consolas">Exercise 10.8</font>
> <font face="楷体">待做</font>

## <font face="Consolas">Exercise 10.9</font>
> <font face="楷体">待做</font>

## <font face="Consolas">Exercise 10.10</font>
> <font face="楷体">待做</font>

## <font face="Consolas">Exercise 10.11</font>
> <font face="楷体">待做</font>
