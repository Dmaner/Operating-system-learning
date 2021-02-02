#include <stdio.h>

int add(int a, int b){
    printf("Add number\n");
    return a + b;
}

int main()
{
    int a, b;
    a = 1;
    b = 2;
    int res = add(a, b);
    printf("Result: %d\n", res);
    return 0;
}
