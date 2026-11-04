#include <stdio.h>

int num(void)
{
    static int num = 0;
    num++;

    return num;
}

int main()
{
    int n = 0;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
    {
        printf("i = %d, num = %d\n", i, num());
    }
    return 0;
}