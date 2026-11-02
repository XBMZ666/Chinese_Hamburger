```c
#define MAXSIZE 100
#include <stdio.h>





//要想使用顺序表, 需要定义一个结构体类型, 该结构体类型的成员元素为一个数组和一个整型变量
//之后用该结构体类型定义一个结构体变量, 这个结构体变量就是顺序表
//在顺序表中, 数组用于存储顺序表中的数据元素, 整型变量用于记录顺序表的长度
typedef struct
{
    int data[MAXSIZE];
    int length;
}SeqList;





//顺序表的初始化, 即把顺序表的长度设置为0
//在初始化顺序表之前, 需要先定义一个顺序表, 然后将顺序表的地址传递给函数
//定义顺序表后, 调用以下函数即可完成顺序表的初始化
void initList(SeqList * list)
{
    list->length = 0;
}





//在顺序表的尾部添加一个元素
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





//遍历顺序表, 即依次访问顺序表中（数组）中的每一个元素, 并把它们打印出来
void listElem(SeqList * list)
{
    if (list->length == 0)
    {
        printf("顺序表为空, 无法遍历\n");

        return;
    }

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





//根据位置, 在顺序表中插入一个元素
void insertElem(SeqList * list, int pos, int elem)
{
    if (pos > list->length || pos < 1)
    {
        printf("插入位置不合法, 无法插入元素\n");

        return;
    }

    else
    {
        for (int i = list->length; i >= pos; i--)
        {
            list->data[i] = list->data[i - 1];
        }

        list->data[pos - 1] = elem;
        list->length++;
        
        return;
    }
}




/*
错误示范！删除顺序表中指定位置的元素, 实际上就是让顺序表中指定位置的元素被之后的元素覆盖掉, 然后顺序表的长度减1
为了实现覆盖, 需要从顺序表中指定位置的下一个位置开始, 所有元素依次向前覆盖一个位置
但是如果遍历时是从后往前, 那么就会导致指定位置后的所有元素都被覆盖成最后一个位置的元素
void deleteElem(SeqList * list, int pos, int * elem)
{
    if (pos > list->length || pos < 1)
    {
        printf("删除位置不合法, 无法删除元素\n");
        
        return;
    }

    else
    {
        *elem = list->data[pos - 1];

        for (int i = list->length - 1; i >= pos; i--)
        {
            list->data[i - 1] = list->data[i];
        }

        list->length--;
        
    }
}
*/


//删除顺序表中指定位置的元素, 实际上就是让顺序表中指定位置的元素被之后的元素覆盖掉, 然后顺序表的长度减1
//为了实现覆盖, 需要从顺序表中指定位置的下一个位置开始, 所有元素依次向前覆盖一个位置
void deleteElem(SeqList * list, int pos, int * elem)
{
    if (pos > list->length || pos < 1)
    {
        printf("删除位置不合法, 无法删除元素\n");
        
        return;
    }
    
    else
    {
        *elem = list->data[pos - 1];

        for (int i = pos; i < list->length; i++)
        {
            list->data[i - 1] = list->data[i];
        }

        list->length--;
    }
    
}





//给定值, 在顺序表中查找该值第一次出现的位置
//如果该值在顺序表中不存在, 则返回-1
int findElem(SeqList * list, int target)
{
    for (int i = 0; i < list->length; i++)
    {
        if (list->data[i] == target)
        {
            return i + 1;
        }
    }

    return -1;
}







int main()
{
    SeqList list;     //定义了一个结构体, 这个结构体其实就是顺序表

    initList(&list);

    listElem(&list);

    appendElem(&list, 1);
    appendElem(&list, 2);
    appendElem(&list, 3);
    
    listElem(&list);

    insertElem(&list, 2, 66);
    insertElem(&list, 4, 55);
    listElem(&list);

    int elem = 0;
    deleteElem(&list, 2, &elem);
    printf("此次删除顺序表中第2个元素, 删除的元素是: %d\n", elem);
    listElem(&list);
    
    int find = 0;
    find = findElem(&list, 25);
    printf("查找顺序表中值为25的元素, 该元素第一次出现的位置是: %d\n", find);
    find =findElem(&list, 55);
    listElem(&list);
    printf("查找顺序表中值为55的元素, 该元素第一次出现的位置是: %d\n", find);

    return 0;
}
```