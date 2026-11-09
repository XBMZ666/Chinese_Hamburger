求最大公约数和最小公倍数：辗转相除法求最大公约数, 最小公倍数即两数乘积再除以最大公约数

```c
#include <stdio.h>

// int ouji (int a, int b)
// {
//     while (a % b != 0)
//     {
//         int value = 0;
        
//         value = a % b;
//         a = b;
//         b = value;
//     }

//     return b;
// }

int ouji (int a, int b)
{
    while (b != 0)
    {
        int value = 0;

        value = a % b;

        a = b;

        b = value;
    }

    return a;
}

int main()
{
    int M = 0;
    int N = 0;

    scanf("%d %d", &M, &N);

    printf("%d", ouji(M, N));
    printf(" ");
    printf("%d\n", M * N /ouji(M, N));
    return 0;
}
```