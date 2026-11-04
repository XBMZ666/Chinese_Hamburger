#include <stdio.h>

int main()
{
    char c = 0;
    int sum = 0;

    while ((c = getchar()) != EOF)
    {
        sum++;
    }

    printf("\n%d\n", sum);
    return 0;
}