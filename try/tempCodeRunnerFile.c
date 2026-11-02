
    if (pos > list->length || pos < 1)
    {
        printf("插入位置不合法, 无法插入元素\n");

        return;
    }

    else
    {
        for (int i = list->length; i >= pos; i--)