输入一个年月日, 判断输入日期是这一年的第几天

```c
#include <stdio.h>

int main()
{
    int y = 0;
    int m = 0;
    int d = 0;

    scanf("%d/%d/%d", &y, &m, &d);

    int flag = 0;

    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
    {
        flag = 1;
    }

    int sum = 0;
    sum = d;

    switch (m - 1)
    {
        case 11:
        {
            sum += 30;
        }

        case 10:
        {
            sum += 31;
        }

        case 9:
        {
            sum += 30;
        }

        case 8:
        {
            sum += 31;
        }

        case 7:
        {
            sum += 31;
        }

        case 6:
        {
            sum += 30;
        }

        case 5:
        {
            sum += 31;
        }

        case 4:
        {
            sum += 30;
        }

        case 3:
        {
            sum += 31;
        }

        case 2:
        {
            if (flag)
            {
                sum += 29;
            }
            
            else
            {
                sum += 28;
            }
        }

        case 1:
        {
            sum += 31;
        }
    }

    printf("%d\n", sum);
    return 0;
}
```