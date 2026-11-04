#include <stdio.h>

#include <ctype.h>

int main()
{
    char c = 0;

    int numx = 0;
    int numy = 0;
    int numz = 0;
    while((scanf("%c", &c)) != EOF && c != '#' )
    {
        if(c == ' ')
        {
            numx++;
        }

        else if(c == '\n')
        {
            numy++;
        }

        else
        {
            numz++;
        }
    }

    printf("%d %d %d\n", numx, numy, numz);
    return 0;
}