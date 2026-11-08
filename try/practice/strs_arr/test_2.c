#include <stdio.h>

int main()
{
    char strs[3][7] = {"Apple", "Banana", "Cherry"};

    printf("The second type:\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", strs[i]);
    }
    
    return 0;
}