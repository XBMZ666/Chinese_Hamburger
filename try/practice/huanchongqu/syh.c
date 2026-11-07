#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

/*
缓冲区的定义
*/

typedef struct strbuf
{
    int len;     
    int alloc;      
    char * buf;     
}SB;

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
        return;
    }
}

int strbuf_getline(SB * sb, FILE * fp)
{
    if (sb == NULL)
    {
        printf("未找到传入的缓冲区\n");
        return;
    }
}
/*
CHALLENGE
*/

SB** strbuf_split_buf(const char* str, size_t len, int terminator, int max)


bool strbuf_begin_judge(char* target_str, const char* str, int strlen)


char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len)

