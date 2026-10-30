#include <stdio.h>

int max(int * arr, int n)
{
    int max = 0;

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

    return max;
}

int main()
{
    int arr[50] = {0};
    
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    printf("%d\n", max(arr, n));
    
    return 0;
}