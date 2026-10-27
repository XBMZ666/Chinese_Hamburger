#include <stdio.h>

int main()
{
    printf("days:");
    int total = 0;
    scanf("%d", &total);

    int week = 0;
    int day = 0;

    week = total / 7;
    day = total % 7;

    printf("%d days are %d weeks, %d days.", total, week, day);

    return 0;
}