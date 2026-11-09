int ouji (int a, int b)
{
    while (a % b != 0)
    {
        int value = 0;
        
        value = a % b;
        a = b;
        b = value;
    }

    return b;
}