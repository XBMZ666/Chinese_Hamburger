输入一串整数并逐个读取, 将读入的正奇数累加, 如果读入了非正整数则结束读取, 最终打印输出累加的和

```c
#include <stdio.h>

int main()
{
    int n = 0;

    int sum = 0;

    while (1)
    {
        scanf("%d", &n);

        if (n <= 0)
        {
            break;
        }

        else
        {
            if (n % 2 != 0)
            {
                sum += n;
            }
        }
    }

    printf("%d", sum);
    
    return 0;
}
```