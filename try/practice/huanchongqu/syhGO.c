#include "strbuf.h"
#include <ctype.h>

/*
缓冲区的定义
*/

typedef struct strbuf SB;

/*
Part 2A
*/

void strbuf_init(SB * sb, size_t alloc)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    sb->buf = NULL;
    sb->len = 0;
    sb->alloc = 0;

    if (alloc == 0)
    {
        return;
    }

    sb->buf = (char *)malloc(sizeof(char) * alloc);

    if (sb->buf == NULL)
    {
        printf("内存可能已满\n");
        exit(1);
    }

    sb->buf[0] = '\0';

    sb->alloc = alloc;

    return;
}


void strbuf_attach(SB * sb, void * str, size_t len, size_t alloc)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    if (sb->buf != NULL)
    {
        free(sb->buf);
    }

    sb->buf = (char *)str;

    sb->len = len;
    sb->alloc = alloc;

    return;
}


void strbuf_release(SB * sb)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    if (sb->buf != NULL)
    {
        free(sb->buf);
    }

    sb->buf = NULL;
    sb->len = 0;
    sb->alloc = 0;

    return;
}


void strbuf_swap(SB * a, SB * b)
{
    if (a == NULL || b == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    SB temp;

    temp = *b;

    *b = *a;
    *a = temp;

    return;
}


char * strbuf_detach(SB * sb, size_t * sz)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return NULL;
    }

    char * str;
    
    str = sb->buf;

    *sz = sb->alloc;

    sb->buf = NULL;
    sb->len = 0;
    sb->alloc = 0;

    return str;
}


int strbuf_cmp(const SB * first, const SB * second)
{
    if (first == NULL || second == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return -1;
    }

    if (first->len != second->len)
    {
        return 1;
    }

    return strcmp(first->buf, second->buf);
}


void strbuf_reset(SB * sb)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    sb->buf[0] = '\0';
    sb->len = 0;

    return;
}

/*
Part 2B
*/

void strbuf_grow(SB * sb, size_t extra)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    size_t need;
    need = sb->len + 1 + extra;

    if (need <= sb->alloc)
    {
        return;
    }

    size_t newalloc;
    newalloc = sb->alloc;
    
    while (newalloc < need)
    {
        newalloc *= 2;
    }

    char * newbuf;
    newbuf = (char *)realloc(sb->buf, newalloc);

    if (newbuf == NULL)
    {
        printf("内存可能已满\n");
        exit(1);
    }

    sb->buf = newbuf;
    sb->alloc = newalloc;

    return;
}


void strbuf_add(SB * sb, const void * data, size_t len)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    strbuf_grow(sb, len);

    memcpy(sb->buf + sb->len, data, len);

    sb->len = sb->len + len;

    sb->buf[sb->len] = '\0';

    return;
}


void strbuf_addch(SB * sb, int c)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }
    
    strbuf_grow(sb, sizeof(char));

    sb->buf[sb->len] = (char)c;
    
    sb->len++;

    sb->buf[sb->len] = '\0';

    return;
}


void strbuf_addstr(SB * sb, const char * s)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    strbuf_add(sb, s, strlen(s));

    return;
}


void strbuf_addbuf(SB * sb, const SB * sb2)
{
    if (sb == NULL || sb2 == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    strbuf_add(sb, sb2->buf, sb2->len);

    return;
}


void strbuf_setlen(SB * sb, size_t len)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    sb->len = len;

    sb->buf[len] = '\0';

    return;
}


size_t strbuf_avail(const SB * sb)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return 1;
    }

    return (sb->alloc - (sb->len + 1));
}


void strbuf_insert(SB * sb, size_t pos, const void * data, size_t len)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    strbuf_grow(sb, len);

    memmove(sb->buf + pos + len, sb-> buf + pos, sb->len - pos);

    memcpy(sb->buf + pos, data, len);

    sb->len += len;
    sb->buf[sb->len] = '\0';

    return;
}

/*
Part 2C
*/

void strbuf_ltrim(SB * sb)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    int i = 0;

    while (i < sb->len && isspace(sb->buf[i]))
    {
        i++;
    }

    if (i == 0)
    {
        return;
    }

    memmove(sb->buf, sb->buf + i, sb->len - i + 1);

    sb->len -= i;

    return;
}


void strbuf_rtrim(SB * sb)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    while (sb->len > 0 && isspace(sb->buf[sb->len - 1]))
    {
        sb->len--;
    }

    sb->buf[sb->len] = '\0';

    return;
}


void strbuf_remove(SB * sb, size_t pos, size_t len)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }

    if (pos + len > sb->len) 
    {
        len = sb->len - pos;
    }
    
    memmove(sb->buf + pos, sb->buf + pos + len, sb->len - (pos + len));

    sb->len -= len;
    sb->buf[sb->len] = '\0';
}


/*
Part 2D
*/

ssize_t strbuf_read(SB * sb, int fd, size_t hint)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return 1;
    }

    if (hint == 0)
    {
        hint = 8192;
    }

    strbuf_grow(sb, hint);

    size_t total = 0;
    size_t n = 0;
    FILE * fp = NULL;

    while (1)
    {
        strbuf_grow(sb, 8192);

        size_t avail = 0;
        avail = strbuf_avail(sb);

        if (avail == 0)
        {
            break;
        }

        ssize_t n;
        n = read(fd, sb->buf + sb->len, avail);

        if (n > 0)
        {
            total += n;

            sb->len += n;
            sb->buf[sb->len] = '\0';
        }

        else
        {
            break;
        }
    }

    return total;
}


int strbuf_getline(SB * sb, FILE * fp)
{
    if (sb == NULL || fp == NULL)
    {
        printf("未找到传入的缓冲区或文件\n");
        return -1;
    }
    
    char c = 0;
    int read = 0;
    
    while ((c = fgetc(fp)) != EOF) 
    {
        read = 1;

        if (c == '\n') 
        {
            break;
        }

        strbuf_addch(sb, c);
    }
    
    if (!read && c == EOF) 
    {
        return -1;
    }
    
    return sb->len;
}

/*
CHALLENGE
*/

SB ** strbuf_split_buf(const char* str, size_t len, int terminator, int max)
{
    SB ** part;
    part = (SB **)malloc(sizeof(SB *) * (len + 1));

    if (part == NULL) 
    {
        printf("内存可能已满\n");
        exit(1);
    }

    size_t start = 0;
    int num = 0;

    while (start < len && (max <= 0 || num < max))
    {
        while (start < len && str[start] == terminator)
            start++;

        if (start == len)
            break;

        size_t end = 0;
        end = start;
        while (end < len && str[end] != terminator)
        {
            end++;
        }

        SB *sb;
        sb = (SB *)malloc(sizeof(SB));

        if (sb == NULL) 
        {
            printf("内存可能已满\n");
            exit(1);
        }

        strbuf_init(sb, end - start + 1);
        strbuf_add(sb, str + start, end - start);

        part[num] = sb;
        num++;
        start = end;
    }

    part[num] = NULL;

    return part;
}


bool strbuf_begin_judge(char* target_str, const char* str, int strlen)
{
    if (strlen == 0) 
    {
        return true;
    }

    if (target_str == NULL || str == NULL || strlen < 0)
    {
        return false;
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (i >= strlen || str[i] != target_str[i])
        {
            return false;
        }
    }

    return true;
}


char * strbuf_get_mid_buf(char * target_buf, int begin, int end, int len)
{
    if (target_buf == NULL || begin < 0 || begin > end || end > len)
    {
        return NULL;
    }

    char * p;

    p = (char *)malloc(end - begin + 1);

    if (p == NULL)
    {
        printf("内存可能已满\n");
        exit(1);
    }

    for(int i = 0; i < end - begin; i++)
    {
        p[i] = target_buf[begin + i];
    }

    p[end - begin] = '\0';

    return p;
}

//终！于！全！过！了！
