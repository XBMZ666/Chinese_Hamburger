#include <stdio.h>

int main()
{
    int height = 0;
    
    printf("height:");

    scanf("%d", &height);

    double inch = 0;

    inch = height * 2.54;

    printf("%f", inch);
    return 0;
}