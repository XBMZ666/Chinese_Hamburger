#include <stdio.h>

int main()
{
    char arr[60] = {0};

    char c = 0;

    int i = 0;
    while(scanf("%c", &c) != EOF)
    {
        if(c == '\n')
        {
            break;
        }

        i++;

        arr[i] = c;
    }

    printf("\"%s\"\n", arr + 1);

    printf("\"%20s\"\n", arr + 1);

    printf("\"%-20s\"\n", arr + 1);
    return 0;
}