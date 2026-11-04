#include <stdio.h>

double difference(double * arr, int n)
{
    double max = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            max = arr[i];
        }

        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    double min = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            min = arr[i];
        }

        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return max - min;
}

int main()
{
    double arr[50] = {0};
    
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%lf", arr + i);
    }

    printf("difference between max and min = %lf\n", difference(arr, n));
    return 0;
}