#include <stdio.h>

int main()
{
    int nums[4] = {1, 2, 3, 1};
    int numsSize = 4;

    for (int i = 0; i < numsSize - 1; i++)
    {
        int change = 0;
        for (int j = 0; j < numsSize - 1 - i; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                int value = 0;
                value = nums[j + 1];
                nums[j + 1] = nums[j];
                nums[j] = value;
            }
        }
        if (!change)
        {
            break;
        }
    }

    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }

    for (int i = 0; i < numsSize - 1; i++)
    {
        if (nums[i] = nums[i + 1])
        {
            printf("True");
            return 0;
        }
    }

    printf("False");
    return 0;
}