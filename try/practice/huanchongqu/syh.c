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
        printf("未找到缓冲区\n");
        return;
    }

    sb->len = 0;
    sb->alloc = 0;
    sb->buf = NULL;

    if (alloc == NULL)
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
}


void strbuf_attach(SB * sb, void * str, size_t len, size_t alloc)


void strbuf_release(SB * sb)


void strbuf_swap(SB * a, SB * b)


char * strbuf_detach(SB * sb, size_t * sz)


int strbuf_cmp(const SB * first, const SB * second)


void strbuf_reset(SB * sb)

/*
Part 2B
*/

void strbuf_grow(SB * sb, size_t extra)


void strbuf_add(SB * sb, const void * data, size_t len)


void strbuf_addch(SB * sb, int c)


void strbuf_addstr(SB * sb, const char * s)


void strbuf_addbuf(SB * sb, const SB * sb2)


void strbuf_setlen(SB * sb, size_t len)


size_t strbuf_avail(const SB * sb)


void strbuf_insert(SB * sb, size_t pos, const void * data, size_t len)

/*
Part 2C
*/

void strbuf_ltrim(SB * sb)


void strbuf_rtrim(SB * sb)


void strbuf_remove(SB * sb, size_t pos, size_t len)

/*
Part 2D
*/

ssize_t strbuf_read(SB * sb, int fd, size_t hint)


int strbuf_getline(SB * sb, FILE * fp)

/*
CHALLENGE
*/

SB** strbuf_split_buf(const char* str, size_t len, int terminator, int max)


bool strbuf_begin_judge(char* target_str, const char* str, int strlen);


char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len)

