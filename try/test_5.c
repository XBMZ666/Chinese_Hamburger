#include <stdio.h>
#include <stdlib.h>
#define typeElem int

typedef struct
{
    typeElem data;
    struct Node * next;
}Node;

Node * initList()
{
    Node * head = (Node *)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

void addElem(Node * head, typeElem elem)
{
    Node * p = (Node *)malloc(sizeof(Node));
    p->data = elem;
    p->next = head->next;
    head->next = p;
}

Node * getTail(Node * head)
{
    Node * p = head;

    while (p-> next != NULL)
    {
        p = p->next;
    }

    return p;
}

void addElemTail(Node * tail, typeElem elem)
{
    Node * p = (Node *)malloc(sizeof(Node));
    p->data = elem;
    tail->next = p;
    p->next = NULL;
}



void listElem(Node * head)
{
    Node * p = head->next;

    if (p == NULL)
    {
        printf("啥也没有, 只有一个头结点\n");
        return;
    }

    int first = 1;
    while (p != NULL)
    {
        if (first)
        {
            first = 0;

        }

        else
        {
            printf(" ");
        }

        printf("%d", p->data);
        p = p->next;
    }

    printf("\n");
}

void listElem(int )

void deleteElem()

void appendElem()
{
    return 0;
}


int main()
{
    Node * head;
    head = initList();

    listElem(head);

    addElem(head, 88);
    addElem(head, 99);

    listElem(head);

    addElemTail(getTail(head), 345);
    listElem(head);
    return 0;
}