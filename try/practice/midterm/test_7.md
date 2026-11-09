循环中同时计算阶乘和对阶乘求和

```c
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
```