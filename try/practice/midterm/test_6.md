兔子繁衍问题：斐波那契数列的变种, 求大于一个正整数N的, 在斐波那契数列中的, 最接近N的项的下标

```c
#include <stdio.h>

int main()
{
    int N = 0;
    scanf("%d", &N);

    if (N == 1)
    {
        printf("%d", 1);
        return 0;
    }

    int a = 1;
    int b = 1;

    int k = 2;

    while (1)
    {
        if (b >= N)
        {
            break;
        }

        int value = 0;
        value = a + b;
        a = b;
        b = value;

        k++;
    }

    printf("%d\n", k);

    return 0;
}

// int feibo(int n)
// {
//     int a = 1;

//     int b = 1;

//     for (int i = 3; i <= n; i++)
//     {
//         int value = 0;

//         value = a + b;

//         a = b;

//         b = value;
//     }

//     if (n == 1)
//     {
//         return a;
//     }

//     else if (n == 2)
//     {
//         return b;
//     }

//     else
//     {
//         return b;
//     }
// }

// int main()
// {
//     int N = 0;
//     scanf("%d", &N);

//     for (int i = 1; ; i++)
//     {
//         if (feibo(i) >= N)
//         {
//             printf("%d\n", i);

//             return 0;
//         }
//     }

//     return 0;
// }
```