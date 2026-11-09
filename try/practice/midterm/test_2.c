#include <stdio.h>

int main()
{
    int n = 0;

    int sum = 0;

    while (1)
    {
        scanf("%d", &n);

        if (n <= 0)
        {
            break;
        }

        else
        {
            if (n % 2 != 0)
            {
                sum += n;
            }
        }
    }

    printf("%d", sum);
    
    return 0;
}