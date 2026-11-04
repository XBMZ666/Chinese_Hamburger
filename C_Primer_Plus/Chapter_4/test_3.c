#include <stdio.h>

int main()
{
    double x = 0;

    scanf("%lf", &x);

    printf("The input is %.1f or %.1e\n", x, x);
    printf("The input is %+.3f or %.3E\n", x, x);
    return 0;
}