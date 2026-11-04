#include <stdio.h>

int main()
{
    char arr[26] = {0};

    for(char c = 'a'; c <= 'z'; c++)
    {
        arr[c - 'a'] = c;
    }

    for(int i = 0; i < 26; i++)
    {
        printf("%c ", arr[i]);
    }
    return 0;
}