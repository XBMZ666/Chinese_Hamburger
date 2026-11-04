#include <stdio.h>
#include <math.h>

double min(double x, double y)
{
    double epsilon = 1e-9;
    
    if (x < y - epsilon)
    {
        return x;
    }

    else
    {
        return y;
    }
}

int main()
{
    double a = 0;
    double b = 0;

    printf("a = ");
    scanf("%lf", &a);

    printf("b = ");
    scanf("%lf", &b);

    printf("min = %f\n", min(a, b));
    return 0;
}