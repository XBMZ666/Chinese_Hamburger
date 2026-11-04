#include <stdio.h>
#include <stdlib.h>
#define ElemType int
#define MAX 100





typedef struct
{
    ElemType * data;
    int length;
}SeqList;




//采用动态分配内存来初始化结构体, 则先使用malloc函数, 在堆内存上为结构体开辟一片空间, 再根据返回的指针, 结合->, 来为结构体的成员元素赋值
//类似地, 采用动态分配内存来初始化其他类型的变量时, 先使用malloc函数, 在堆内存上开辟对应大小的空间, 再根据返回的指针, 结合解引用操作符*, 来为变量赋值
//之后, 可以利用返回的指针来代表变量、操作变量
//使用malloc函数必须要包含头文件stdlib.h
SeqList * initList()
{
    SeqList * p;
    p = (SeqList *)malloc(sizeof(SeqList));

    if (p == NULL)
    {
        printf("创建失败\n");

        return NULL;
    }
    
    p->length = 0;

    p->data = (ElemType *)malloc(sizeof(ElemType) * MAX);

    if (p->data == NULL)
    {
        printf("动态数组创建失败\n");

        return NULL;
    }

    return p;
}





void appendElem(SeqList * p, ElemType elem)
{
    p->data[p->length] = elem;
    p->length++;

    return;
}





void listElem(SeqList * p)
{
    if (p->length == 0)
    {
        printf("这个顺序表暂时什么都没有");

        return;
    }

    printf("此时, 顺序表中的元素个数：%d\n", p->length);
    for (int i = 0; i < p->length; i++)
    {
        printf("顺序表中第%d个元素为：%d\n", i + 1, p->data[i]);
    }


    return;
}

int main()
{
    //初始化一个顺序表类型的指针
    SeqList * ptr;

    ptr = initList();

    printf("目前, 顺序表的长度为：%d\n", ptr->length);

    appendElem(ptr, 34);

    printf("目前, 顺序表的长度为：%d\n", ptr->length);

    listElem(ptr);

    appendElem(ptr, 105);
    appendElem(ptr, 250);
    appendElem(ptr, 360);

    listElem(ptr);




    

    return 0;
}
