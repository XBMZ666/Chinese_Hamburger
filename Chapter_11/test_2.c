#include <stdio.h>

char * save(char * arr, int n)
{
    char rubbish = 0;
    rubbish = getchar();
    
    int sum = 0;
    char c = 0;

    while ((c = getchar()) != EOF && sum < n && c != '\n' && c != '\t' && c != ' ')
    {
        arr[sum] = c;
        sum++;
    }

    return arr;
}

int main()
{
    char arr[50] = {0};

    int n = 0;
    scanf("%d", &n);
    
    save(arr, n);

    printf("%s\n", arr);
    return 0;
}
  