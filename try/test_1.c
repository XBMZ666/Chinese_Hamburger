#include <stdio.h>

int main()
{
    char arr[100] = {0};

    int i = 0;
    char c = 0;
    while(scanf("%c", &c) != EOF)
    {
        if(c == '\n')
        {
            break;
        }
        i++;
        arr[i] = c;
    }

    printf("%s\n", arr);

    return 0;
}