独立写出顺序表的定义, 以及顺序表增删减查的函数.
采用动态分配内存.

```c
#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int * data;
    int length;
}SeqList;

SeqList * initList()
{
    SeqList * list = (SeqList *)malloc(sizeof(SeqList));      //此处开辟了一片新内存
    
    list->data = (int *)malloc(sizeof(int) * MAXSIZE);
    list->length = 0;

    return list;
}

void listElem(SeqList * list)
{
    if (list->length == 0)
    {
        printf("顺序表为空, 无法遍历\n");

        return;
    }
    
    else
    {
        for (int i = 0; i < list->length; i++)
        {
            if (i != 0)
            {
                printf(" ");
            }

            printf("%d", list->data[i]);
        }

        printf("\n");

        return;
    }
}

void appendElem(SeqList * list, int elem)
{
    if (list->length >= MAXSIZE)
    {
        printf("顺序表已满, 无法添加元素\n");
    }
    
    else
    {
        list->data[list->length] = elem;
        list->length++;
    }
}

int main()
{
    SeqList * list = initList();      //浅拷贝

    appendElem(list, 2);
    appendElem(list, 5);
    appendElem(list, 12);

    listElem(list);
    
    free(list);      //free函数是用于释放指针所指向的, 在堆内存手动创建的内存空间, 而不是用于释放指针的！此处的指针是在函数内部定义的, 因此占用在栈内存创建的内存空间
    free(list->data);
    return 0;
}
```