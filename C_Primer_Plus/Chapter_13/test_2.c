#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    char arr[120] = {0};

    FILE *fpa;
    FILE *fpb;

    if(argc != 3)
    {
        printf("Failure: please input the source file and destination file.\n");
        exit(EXIT_FAILURE);
    }

    else
    {
        if((fpa = fopen(argv[1], "r")) == NULL)
        {
            printf("Can't open %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        if((fpb = fopen(argv[2], "w")) == NULL)
        {
            printf("Can't open %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }


        int size = 0;
        while ((size = fread(arr, 1, 120, fpa)) > 0)
        {
            fwrite(arr, 1, size, fpb);
        }
    
        int ch = 0;
        while((ch = getc(fpa)) != EOF)
        {
            putc(ch, fpb);
        }

        fclose(fpa);
        fclose(fpb);
    }

    return 0;
}