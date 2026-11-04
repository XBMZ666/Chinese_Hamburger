#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    int ch = 0;
    FILE * fp;
    unsigned long count = 0;

    char name[20] = {0};
    printf("file name: ");
    scanf("%s", name);

    if((fp = fopen(name, "r")) == NULL)
    {
        printf("Can't open %s\n", name);
        exit(EXIT_FAILURE);
    }

    while((ch = getc(fp)) != EOF)
    {
        putchar(ch);
        count++;
    }

    printf("File %s has %lu characters.\n", name, count);

    return 0;
}