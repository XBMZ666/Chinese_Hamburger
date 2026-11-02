
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
    
    free(list);
    free(list->data);
    return 0;
}
