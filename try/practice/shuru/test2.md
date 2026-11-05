```c
#include <stdio.h>

void scanf_line(char * str, int alloc)
{
    int c = 0;
    int index = 0;

    while ((c = fgetc(stdin)) != EOF)
    {
        if (c == '\n')
        {
            break;
            //回车代表一行结束了, 不再读取了, 剩下的字符都扔缓冲区里
            //这个回车已经被读取了, 而此时并未把它放到字符数组里面, 它就被废弃掉了
        }

        if (index < alloc - 1)
        {
            str[index] = (char)c;
            index++;
        }

        else
        {
            break;
            //字符串里面加上\0已经满了, 不再读取了, 剩下的字符都扔缓冲区里
        }
    }

    //读取结束后, 别忘了手动给字符型数组中补\0
    str[index] = '\0';
}

int main()
{
    char str[100] = {0};

    printf("请输入一行字： ");

    scanf_line(str, 100);

    printf("你刚刚输入的内容是： %s\n", str);

    //尝试一下读取多行
    int n = 0;
    printf("请输入你要读取的行数n = ");

    scanf("%d", &n);

    //输入n的值后, 回车后, 由于缓冲区没有内容, 所以将从屏幕上读取输入的内容
    //每输入一行内容并回车后, 回车会使这行内容进入缓冲区, 被函数读取, 读取后则随即被打印输出
    for (int i = 1; i <= n; i++)
    {
        char manystrs[50] = {0};

        scanf_line(manystrs, 50);

        printf("一行内容：%s\n", manystrs);
    }

    return 0;
}
```