#include <stdio.h>

// 105分钱 ×
// 150分钱 √
// 5分 2分 1分 共100枚

int main()
{
    int n = 0;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 100 - i; j++)
        {
            if (150 - i * 5 - j * 2 == 100 - i - j)
            {
                printf("%d %d %d\n", i , j, 100 - i - j);
            }
        }
    }
    return 0;
}