#include <stdio.h>
#include <string.h>

int main()
{
    char word[30] = {0};


    int sum = 0;
    int num = 0;
    while(scanf("%s", word) != EOF)
    {
        num++;

        int numc = 0;
        numc = strlen(word);
        sum += numc;
    }

    double average = 0;

    average = (sum * 1.0) / num;

    printf("\naverage = %.1f\n", average);

    return 0;
}