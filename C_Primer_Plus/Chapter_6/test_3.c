#include <stdio.h>

int main()
{
    for(int i = 1; i <= 6; i++)
    {
        char c = 'F';
        for(int j = 1; j <= i; j++)
        {
            printf("%c", c);
            c--;
        }
        
        printf("\n");
    }
    return 0;
}