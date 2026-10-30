#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char name[20] = {0};
    printf("file name: ");
    scanf("%s", name);
    
    char c = 0;

    if((fp = fopen(name, "r")) == NULL)
    {
        printf("Can't open %s\n", name);
        exit(EXIT_FAILURE);
    }

    while((c = getc(fp)) != EOF)
    {
        if(isalpha(c))
        {
            putchar(toupper(c));
        }

        else
        {
            putchar(c);
        }
    }
    
    fclose(fp);
    return 0;
}