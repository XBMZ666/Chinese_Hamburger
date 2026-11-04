#include <stdio.h>
#include <stdlib.h>
#define ElemType int

//链表可以视作由若干个“结点”构成的数据结构
//每个结点中存储着某些数据, 特别的是, 每个结点中还存储着下一个结点的地址
//结点的实质是结构体
//此处定义了一个结构体类型, 即结点类型
typedef struct node
{
    ElemType * data;      //这里采用动态分配内存, 结点的成员元素data是一个指针, 通过操作指针data来为该结点存储数据
    //最终需要遍历每个结点, 把每个结点的data所指向的内存区域释放

    struct node * next;      //结点的成员元素next是一个指针, 存储着下一个结点的地址, 指向下一个结点
}Node;



//初始化一个链表, 就是创建一个头结点, 此时由于并无其他结点, 故头结点的next为空指针, 没有指向的内容. 头结点里面不存放有效内容
Node * initList()
{
    Node * head = (Node *)malloc(sizeof(Node));

    head->next = NULL;

    head->data = (ElemType *)malloc(sizeof(ElemType));

    *(head->data) = 0;

    return head;
}



//头插法插入元素
//插入前, 需要先创造一个结点来存储元素和下一个结点的地址
void headinsert(Node * head, ElemType elem)
{
    Node * p = (Node *)malloc(sizeof(Node));

    p->data = (ElemType *)malloc(sizeof(ElemType));

    p->data[0] = elem;

    p->next = head->next;

    head->next = p;

    return;
}



void listElem(Node * head)
{
    Node * p;
    p = head;

    if (p->next == NULL)
    {
        printf("这个链表中尚且只有一个头结点\n");

        return;
    }

    int first = 1;
    while (p->next != NULL)
    {
        if (first)
        {
            first = 0;
        }

        if (!first)
        {
            printf(" ");
        }

        p = p->next;
        printf("%d", p->data[0]);
    }

    printf("\n");

    return;
}


int main()
{
    Node * head;
    
    head = initList();

    listElem(head);

    headinsert(head, 35);

    listElem(head);

    headinsert(head, 57);
    headinsert(head, 99);
    headinsert(head, 25);

    listElem(head);
    
    return 0;
}