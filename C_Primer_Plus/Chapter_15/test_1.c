#include <stdio.h>
#include <string.h>

int value(char * arr)
{
    int n = 0;
    n = strlen(arr);

    int k = 0;
    int mul = 1;
    int sum = 0;
    while (k < n)
    {
        int value = 0;
        value = arr[k] == '0' ? 0 : 1;
        sum += value * mul;
        k++;
        
        mul *= 2;

    }

    return sum;
}

int main()
{
    char string[60] = {0};
    printf("string:");
    scanf("%s", string);
    char * c = string;
    value(c);

    printf("value = %d\n", value(c));
    return 0;
}