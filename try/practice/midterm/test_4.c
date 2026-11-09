#include <stdio.h>

int main()
{
    int n = 0;

    scanf("%d", &n);

    long long fact = 1;

    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }

    printf("fact = %lld", fact);

    return 0;
}