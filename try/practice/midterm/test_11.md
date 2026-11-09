2000年是20世纪, 2001年是21世纪, 2100年是21世纪, 2101年是22世纪

```c
#include <stdio.h>

int run(int y)
{
    return (y % 4 == 0 && y % 100 != 0 || y % 400 == 0);
}

int main()
{
    int y = 0;
    scanf("%d", &y);

    if (y <= 2000 || y >= 2101)
    {
        printf("Invalid year!");

        return 0;
    }

    int empty = 1;      

    int sum = 0;
    for (int i = 2001; i <= y; i++)
    {
        if(run(i))
        {
            empty = 0;

            printf("%d\n",i);
        }
    }

    //到这个位置, 可能是打印输出了一堆东西, 也可能啥也没打印输出, 所以需要判断
    if (empty)
    {
        printf("None");
    }


    return 0;
}
```