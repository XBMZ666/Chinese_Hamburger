#include <stdio.h>

void binary(int n)
{
    if(n > 1)
    {
        binary(n >> 1);
    }

    putchar((n & 1) == 0 ? '0' : '1');
}

int judge(int value, int position)
{
    int k = 1;

    while (k < position)
    {
        value /= 2;
        k++;
    }

    return (value & 1);
}

int main()
{
    int n = 0;
    int m = 0;
    
    printf("n = ");
    scanf("%d", &n);

    printf("m = ");
    scanf("%d", &m);

    binary(n);
    printf("\n");

    if (judge(n, m))
    {
        printf("Yes\n");
    }

    else
    {
        printf("No\n");
    }
    return 0;
}