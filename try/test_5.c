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

void listElem(Node * head)
{
    Node * p = head->next;

    if (p == NULL)
    {
        printf("啥也没有, 只有一个头结点");
        return;
    }

    while (p != NULL)
    {
        printf("%d", p->data);
        p = p->next;
    }
}

int main()
{
    Node * head;
    head = initList();

    listElem(head);

    addElem(head, 88);
    addElem(head, 99);

    listElem(head);
    return 0;
}