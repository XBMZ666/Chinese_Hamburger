循环中同时计算1到n的和并对这个和求和

```c
#include <stdio.h>

int main()
{
    int n = 0;

    scanf("%d", &n);

    int sum = 0;
    int SUM = 0;

    for (int i = 1; i <= n; i++)
    {
        sum += i;

        SUM += sum;
    }

    printf("sum = %d\n", SUM);

    return 0;
}
```