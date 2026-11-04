#include <stdio.h>

void chline(char ch, int j, int i)
{
    for (int a = 1; a <= i; a++)
    {
        for (int b = 1; b <= j; b++)
        {
            printf("%c", ch);
        }
        printf("\n");
    }
}

int main()
{
    char c = 0;
    int i = 0;
    int j = 0;
    
    printf("c = ");
    scanf("%c", &c);

    printf("i = ");
    scanf("%d", &i);

    printf("j = ");
    scanf("%d", &j);
    
    chline(c, j, i);

    return 0;
}