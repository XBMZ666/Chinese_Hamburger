#include <stdio.h>

int main()
{
    int N = 0;
    scanf("%d", &N);

    long long mul = 1;
    long long sum = 0;
    for (int i = 1; i <= N; i++)
    {
        mul *= i;
        sum += mul;
    }

    printf("%lld\n", sum);
    
    return 0;
}