#include <stdio.h>

int main()
{
    int n = 0;

    scanf("%d", &n);

    int a = 1;
    int b = 1;

    for (int i = 3; i <= n; i++)      //i只决定循环多少次, 循环体内的具体递推是由a、b、临时变量共同来实现的
    {
        int value = 0;

        value = a + b;
        a = b;
        b = value;
    }

    if (n == 1)
    {
        printf("%d\n", a);
    }

    else if (n == 2)
    {
        printf("%d\n", b);
    }

    else
    {
        printf("%d\n", b);
    }

    return 0;
}