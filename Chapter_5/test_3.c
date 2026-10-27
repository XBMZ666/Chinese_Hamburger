#include <stdio.h>

double cube(double n)
{
    return (n * n * n);
}

int main()
{
    printf("Enter a number:");
    double n = 0;
    scanf("%lf", &n);

    printf("%f", cube(n));
    
    return 0;
}