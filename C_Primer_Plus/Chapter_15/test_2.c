#include <stdio.h>

void binary(int n)
{
    if(n > 1)
    {
        binary(n >> 1);
    }

    putchar((n & 1) == 0 ? '0' : '1');
}

int num(int n)
{
    int sum = 0;

    while (n != 0)
    {
        int rest = 0;
        rest = n % 2;

        if (rest)
        {
            sum++;
        }

        n /= 2;
    }

   return sum;
}

int main()
{
    int n = 0;
    scanf("%d", &n);

    binary(n);
    printf("\n");

    printf("number of 1 = %d\n", num(n));
    return 0;
}