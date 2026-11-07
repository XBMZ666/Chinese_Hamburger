#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
缓冲区的定义
*/

struct strbuf
{
    int len;     
    int alloc;      
    char * buf;     
};

/*
Part 2A
*/

void strbuf_init(struct strbuf * sb, size_t alloc)
{
    sb->buf = (struct strbuf)
    sb->len = 0;
    sb->alloc = alloc;
}


void strbuf_attach(struct strbuf * sb, void * str, size_t len, size_t alloc)


void strbuf_release(struct strbuf * sb)


void strbuf_swap(struct strbuf * a, struct strbuf * b)


char * strbuf_detach(struct strbuf * sb, size_t * sz)


int strbuf_cmp(const struct strbuf * first, const struct strbuf * second)


void strbuf_reset(struct strbuf * sb)

/*
Part 2B
*/

void strbuf_grow(struct strbuf * sb, size_t extra)


void strbuf_add(struct strbuf * sb, const void * data, size_t len)


void strbuf_addch(struct strbuf * sb, int c)


void strbuf_addstr(struct strbuf * sb, const char * s)


void strbuf_addbuf(struct strbuf * sb, const struct strbuf * sb2)


void strbuf_setlen(struct strbuf * sb, size_t len)


size_t strbuf_avail(const struct strbuf * sb)


void strbuf_insert(struct strbuf * sb, size_t pos, const void * data, size_t len)

/*
Part 2C
*/

void strbuf_ltrim(struct strbuf * sb)


void strbuf_rtrim(struct strbuf * sb)


void strbuf_remove(struct strbuf * sb, size_t pos, size_t len)

/*
Part 2D
*/

ssize_t strbuf_read(struct strbuf * sb, int fd, size_t hint)


int strbuf_getline(struct strbuf * sb, FILE * fp)

/*
CHALLENGE
*/

struct strbuf** strbuf_split_buf(const char* str, size_t len, int terminator, int max)


bool strbuf_begin_judge(char* target_str, const char* str, int strlen);


char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len)

