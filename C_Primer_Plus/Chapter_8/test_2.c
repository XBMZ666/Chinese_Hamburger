#include <stdio.h>
#include <ctype.h>

int main()
{
    int sumlower = 0;
    int sumupper = 0;
    char c;

    while((c = getchar()) != EOF)
    {
        if(islower(c))
        {
            sumlower++;
        }

        else if(isupper(c))
        {
            sumupper++;
        }
    }

    printf("lower = %d upper = %d\n", sumlower, sumupper);
    return 0;
}