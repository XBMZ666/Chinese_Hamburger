#include <stdio.h>

int sx(int n)
{
    int flag = 0;

    int a = 0;
    int b = 0;
    int c = 0;

    c = n % 10;
    b = n / 10 % 10;
    a = n / 100 % 10;

    if (a * a * a + b * b * b + c * c * c == n)
    {
        flag = 1;
    }

    return flag;
}

int main()
{
    int M = 0;
    int N = 0;
    scanf("%d %d", &M, &N);

    if (M > N || M < 100 || M > 999)
    {
        printf("Invalid Value.");
        
        return 0;
    }

    for (int i = M; i <= N; i++)
    {
        if (sx(i))
        {
            printf("%d\n", i);
        }
    }

    return 0;
}