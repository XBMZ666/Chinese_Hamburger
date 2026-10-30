#include <stdio.h>

int main()
{
    int num = 0;

    int x = 0;
    int y = 0;
    int sumx = 0;
    int sumy = 0;

    while((scanf("%d", &num)) != EOF && num != 0 )
    {
        if(num % 2 == 0)
        {
            x++;
            sumx += num;
        }

        else
        {
            y++;
            sumy += num;
        }
    }

    double averagex = 0;
    double averagey = 0;

    averagex = (sumx * 1.0) / x;
    averagey = (sumy * 1.0) / y;

    printf("even:%d %.2f\n", x, averagex);
    printf("odd:%d %.2f\n", y, averagey);
    return 0;
}