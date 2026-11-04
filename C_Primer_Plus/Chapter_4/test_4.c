#include <stdio.h>

int main()
{
    double height = 0;

    char name[30] = {0};

    printf("Your height:");
    scanf("%lf", &height);

    printf("Your name:");
    scanf("%s", name);

    printf("%s, you are %.3f feet tall", name, height);
    return 0;
}