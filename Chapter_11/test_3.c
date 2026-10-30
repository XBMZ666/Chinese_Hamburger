#include <stdio.h>

void reverse(char * arr, int n)
{
    char arrcopy[300] = {0};

    for (int i = n - 1; i >= 0; i--)
    {
        arrcopy[n - 1 - i] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = arrcopy[i];
    }

}

int main()
{
    char arr[300] = {0};

    int n = 0;

    scanf("%d", &n);
    scanf("%s", arr);

    reverse(arr, n);

    printf("%s\n", arr);

    return 0;
}