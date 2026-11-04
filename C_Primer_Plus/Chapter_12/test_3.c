#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int change = 0;

        for (int j = 0; j < n - 1 - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                change = 1;

                int value = 0;
                value = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = value;
            }
        }

        if (!change)
        {
            break;
        }
    }
}

int main()
{
    int seed = 0;
    scanf("%d", &seed);

    srand(seed);

    int arr[120] = {0};

    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand() % 10;
    }

    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum++;

        printf("%d", arr[i]);

        if (sum % 10 == 0)
        {
            printf("\n");
        }

        else
        {
            printf(" ");
        }
    }
    
    return 0;
}