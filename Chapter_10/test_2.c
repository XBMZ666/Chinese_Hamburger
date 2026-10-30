#include <stdio.h>

int index(double * arr, int n)
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

    for (int i = 0;i < n; i++)
    {
        if (arr[i] == max)
        {
            return i;
        }
    }
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

    printf("index of the max = %d\n", index(arr, n));
    
    return 0;
}