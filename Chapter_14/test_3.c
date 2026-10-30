#include <stdio.h>

struct name
{
    char a[30];
    char b[30];
};

struct student
{
    struct name NAME;
    double grade[3];
    double average;
};

int main()
{
    struct student arr[4] = {0};

    for (int i = 0; i < 4; i++)
    {
        struct student STUDENT = {0};

        printf("i = %d\n", i);
        printf("namea = ");
        scanf("%s", STUDENT.NAME.a);
        printf("nameb = ");
        scanf("%s", STUDENT.NAME.b);
        printf("grade = ");
        scanf("%lf %lf %lf", &(STUDENT.grade[0]), &(STUDENT.grade[1]), &(STUDENT.grade[2]));

        STUDENT.average = ( (STUDENT.grade[0]) + (STUDENT.grade[1]) + (STUDENT.grade[2]) ) / 3;

        arr[i] = STUDENT;
    }

    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        printf("i = %d, information: namea-%s nameb-%s grade[0]-%.1f grade[1]-%.1f grade[2]-%.1f average-%.1f\n", i, arr[i].NAME.a, arr[i].NAME.b, arr[i].grade[0], arr[i].grade[1], arr[i].grade[2], arr[i].average);
        
        sum += arr[i].average;
    }

    printf("average and average = %.1f\n", sum / 4);



    return 0;
}