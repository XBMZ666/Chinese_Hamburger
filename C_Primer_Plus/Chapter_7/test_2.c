#include <stdio.h>

int main()
{
    char c = 0;

    int sum = 0;
    while((scanf("%c", &c)) != EOF && c != '#' )
    {
        sum++;
        
        if(c == ' ')
        {
            printf("' '-%d", c);
        }

        
        else
        {
            printf("%c-%d", c, c);
        }

        if (sum % 8 == 0)
        {
            printf("\n");
        }

        else
        {
            printf(" ");
        }
    }
    return 0;
}