本题要求编写程序计算某年某月某日是该年中的第几天。

输入格式:
输入在一行中按照格式“yyyy/mm/dd”（即“年/月/日”）给出日期。注意：闰年的判别条件是该年年份能被4整除但不能被100整除、或者能被400整除。闰年的2月有29天。 

输出格式:
在一行输出日期是该年中的第几天。

```c
#include <stdio.h>

int main()
{
    int y=0;
    int m=0;
    int d=0;

    scanf("%d/%d/%d",&y,&m,&d);

    int flag = 0;
    if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
    {
        flag=1;
    }

    int sum=0;
    sum=d;

    switch(m-1)
            {
                case 12:sum+=31;
                case 11:sum+=30;
                case 10:sum+=31;
                case 9:sum+=30;
                case 8:sum+=31;
                case 7:sum+=31;
                case 6:sum+=30;
                case 5:sum+=31;
                case 4:sum+=30;
                case 3:sum+=31;
                case 2:
                    if(flag)
                    {
                        sum+=29;
                    }
                    else
                    {
                        sum+=28;
                    }
                case 1:sum+=31;
            }
    printf("%d",sum);
    return 0;
}
```