百钱买百鸡

```c
#include <stdio.h>

//公鸡每只5元 母鸡每只3元 小鸡1元3只 鸡必须整只买
//100元买100只鸡

int main()
{
    int n = 0;
    scanf("%d", &n);

    int flag = 0;

    int num = 0;

    for (int i = 1; i <= 100; i++)
    {
        for (int j = 1; j <= 100 - i; j++)
        {
            if ((100 - i - j) % 3 == 0)      //最后剩下的一元决定方程有没有解：小鸡的数量首先得是3的倍数
            {
                if (100 - i * 5 - j * 3 == (100 - i - j) / 3)      //以小鸡的价格为等量关系. 左边：总价 - (母鸡和公鸡的总价) 右边：小鸡的数量 × 单价
                {
                    printf("%d %d %d\n", i, j, 100 - i - j);
                    
                    num++;

                    if(num == n)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        }

        if (flag)
        {
            break;
        }
    }

    return 0;
}
```