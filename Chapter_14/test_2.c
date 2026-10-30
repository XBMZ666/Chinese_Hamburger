#include <stdio.h>
#include <string.h>

int days(void)
{

    int year = 0;
    char month[15] = {0};

    printf("year = ");
    scanf("%d", &year);

    printf("month = ");
    scanf("%s", month);

    int monthvalue = 0;

    if (!strcmp(month, "January"))
    {
        monthvalue = 1;
    }

    else if (!strcmp(month, "February"))
    {
        monthvalue = 2;
    }

    else if (!strcmp(month, "March"))
    {
        monthvalue = 3;
    }

    else if (!strcmp(month, "April"))
    {
        monthvalue = 4;
    }

    else if (!strcmp(month, "May"))
    {
        monthvalue = 5;
    }

    else if (!strcmp(month, "June"))
    {
        monthvalue = 6;
    }

    else if (!strcmp(month, "July"))
    {
        monthvalue = 7;
    }

    else if (!strcmp(month, "August"))
    {
        monthvalue = 8;
    }
    
    else if (!strcmp(month, "September"))
    {
        monthvalue = 9;
    }

    else if (!strcmp(month, "October"))
    {
        monthvalue = 10;
    }

    else if (!strcmp(month, "November"))
    {
        monthvalue = 11;
    }

    else if (!strcmp(month, "December"))
    {
        monthvalue = 12;
    }

    int run = 0;
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
    {
        run = 1;
    }

    int sum = 0;
    switch (monthvalue)
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