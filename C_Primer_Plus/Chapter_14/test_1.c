#include <stdio.h>

int days(void)
{

    int year = 0;
    int month = 0;
    int day = 0;

    printf("year = ");
    scanf("%d", &year);

    printf("month = ");
    scanf("%d", &month);

    printf("day = ");
    scanf("%d", &day);

    int run = 0;
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
    {
        run = 1;
    }

    int sum = 0;
    sum = day;
    switch (month - 1)
    {
        case 12:sum += 31;
        case 11:sum += 30;
        case 10:sum += 31;
        case 9:sum += 30;
        case 8:sum += 31;
        case 7:sum += 31;
        case 6:sum += 30;
        case 5:sum += 31;
        case 4:sum += 30;
        case 3:sum += 31;
        case 2:
        if (run)
        {sum += 29;}
        else
        {sum += 28;}
        case 1:sum += 31;
    }

    return sum;
}

int main()
{
    printf("days = %d\n", days());
    return 0;
}