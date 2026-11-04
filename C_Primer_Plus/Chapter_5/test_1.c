#include <stdio.h>

int main()
{
    int num = 0;
    printf("a number:");
    scanf("%d", &num);

    for(int i = num; i <= num + 10; i++)
    {
        printf("%d ", i);
    }
    
    return 0;
}