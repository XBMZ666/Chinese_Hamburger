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

        //这个if不要写成else if, 否则上面的if语句就没什么用了
        else if (!first)
        {
            printf(" ");
        }

        p = p->next;
        printf("%d", p->data[0]);
    }

    printf("\n");

    return;
}



Node * getTail(Node * head)
{
    Node * p = head;

    while (p->next != NULL)
    {
        p = p->next;
    }

    return p;
}



//依旧是, 想往链表中插入元素, 需要先创建一个结点把元素和下一个结点的地址存储起来
void tailinsert(Node * tail, ElemType elem)
{
    Node * p = (Node *)malloc(sizeof(Node));

    p->data = (ElemType *)malloc(sizeof(ElemType));

    p->data[0] = elem;

    tail->next = p;

    p->next = NULL;
}


//这里错的一塌糊涂
// void emptyList(Node * head)
// {
//     Node * p = head;
//     Node * q = p;

//     while (p->next != NULL)
//     {
//         p = p->next;
//         q = p->next->next;
//         free(p->data);
//         free(p);
        
//         p = q;
//     }

//     free(p->data);
//     free(p);
// }



void emptyList(Node * head)
{
    Node * p = head->next;

    while (p != NULL)
    {
        Node * q = p->next;
        free(p->data);
        free(p);
        p = q;
    }

    //原来的head->next处的空间已经被释放了, 那么head->next成了一个野指针
    head->next = NULL;
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

    emptyList(head);

    listElem(head);

    head = initList();

    headinsert(head, 88);
    headinsert(head, 66);
    tailinsert(getTail(head), 33);
    tailinsert(getTail(head), 22);

    listElem(head);

    emptyList(head);

    listElem(head);

    return 0;
}