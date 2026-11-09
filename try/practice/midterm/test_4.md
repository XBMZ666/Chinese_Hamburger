计算阶乘时, 存放乘积的变量需要用`long long`类型来防溢出

```c
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
```