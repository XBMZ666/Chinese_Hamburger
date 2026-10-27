#include <stdio.h>

int main()
{
    int toes = 10;
    int toes_a = 0;
    int toes_b = 0;

    toes_a = toes * 2;
    toes_b = toes * toes;

    printf("toes = %d, double = %d, square = %d", toes, toes_a, toes_b);

    return 0;
}