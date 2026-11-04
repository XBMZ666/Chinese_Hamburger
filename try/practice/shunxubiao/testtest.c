#include <stdio.h>
#include <stdlib.h>
#define ElemType int
#define MAX 100

typedef struct
{
    ElemType * data;
    int length;
}SeqList;



SeqList * initList()
{
    SeqList * p;
    p = (SeqList *)malloc(sizeof(SeqList));

    if (p == NULL)
    {
        printf("顺序表的空间申请失败");

        return NULL;
    }

    p->data = (ElemType *)malloc(sizeof(ElemType) * MAX);

    if (p->data == NULL)
    {
        printf("动态数组的空间申请失败");

        return NULL;
    }

    p->length = 0;

    printf("顺序表的空间、动态数组的空间都申请成功\n");

    return p;
}



void appendElem(SeqList * p, ElemType e)
{
    p->data[p->length] = e;

    p->length++;
}



void listElem(SeqList * p)
{
    if (p->length == 0)
    {
        printf("顺序表中暂无元素\n");

        return;
    }

    for (int i = 0; i < p->length; i++)
    {
        if (i != 0)
        {
            printf(" ");
        }

        printf("%d", p->data[i]);
    }

    printf("\n");

    return;
}



void insertElem(SeqList * p, int pos, ElemType elem)
{
    for (int i = p->length - 1; i >= pos - 1; i--)
    {
        p->data[i + 1] = p->data[i];
    }

    p->data[pos - 1] = elem;

    p->length++;
}



void deleteElem(SeqList * p, int pos, ElemType * target_ptr)
{
    *target_ptr = p->data[pos - 1];

    for (int i = pos; i <= p->length - 1; i++)
    {
        p->data[i - 1] = p->data[i];
    }

    p->length--;
}



int findElem(SeqList * p, ElemType elem)
{
    for (int i = 0; i < p->length; i++)
    {
        if (p->data[i] == elem)
        {
            return i + 1;
        }
    }

    return -1;
}



void emptyList(SeqList * p)
{
    free(p->data);
    free(p);
    p = NULL;
}


int main()
{
    SeqList * ptr;
    
    ptr = initList();

    listElem(ptr);

    appendElem(ptr, 36);
    appendElem(ptr, 42);

    listElem(ptr);

    insertElem(ptr, 1, 55);
    listElem(ptr);

    insertElem(ptr, 3, 73);
    listElem(ptr);

    ElemType elem;
    deleteElem(ptr, 3, &elem);
    listElem(ptr);
    printf("删除了元素：%d\n", elem);

    appendElem(ptr, 59);
    appendElem(ptr, 34);
    insertElem(ptr, 2, 105);
    insertElem(ptr, 1, 50);
    insertElem(ptr, 3, 33);
    appendElem(ptr, 43);
    listElem(ptr);

    printf("查找元素42的位置为：%d\n", findElem(ptr, 42));

    emptyList(ptr);
    //清空顺序表（释放内存）, 之后如果再想用原指针来代表顺序表, 则需要重新初始化！
    //如果不重新初始化, 那么在原指针中存储的地址处, 并未开辟对应的空间

    initList(ptr);

    int n = 0;
    printf("输入n = ");
    scanf("%d", &n);
    printf("接下来输入n个元素：\n");
    for (int i = 0; i < n; i++)
    {
        ElemType k;

        scanf("%d", &k);

        appendElem(ptr, k);
    }

    listElem(ptr);

    return 0;
}