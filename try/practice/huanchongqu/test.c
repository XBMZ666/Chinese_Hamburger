#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//缓冲区的定义
//缓冲区用来存储字符串、字符串的当前长度、字符串的最大容量
struct strbuf
{
    int len;      //字符串长度
    int alloc;      //字符串的最大容量
    char * buf;      //字符串的指针
};

//Part 2A

//已经定义并为缓冲区sb开辟了空间, 现在要初始化缓冲区sb
//初始化缓冲区sb的要求：分别初始化三个成员变量
//初始化成员变量len：初始化为0
//初始化成员变量alloc：初始化为传入的值
//初始化成员变量buf：开辟容量为alloc的空间
void strbuf_init(struct strbuf * sb, size_t alloc)
{
    sb->len = 0;
    sb->alloc = alloc;
    
    sb->buf = (char *)malloc(alloc);
}

//把字符串填充到缓冲区sb里, 其实就是让缓冲区sb来接管字符串str所在的区域, 而字符串str的长度为len, 最大容量为alloc
void strbuf_attach(struct strbuf * sb, void * str, size_t len, size_t alloc)
{
    sb->len = len;
    sb->alloc = alloc;
    sb->buf = (char *)str;
}

//释放缓冲区sb：先把缓冲区sb里面存的字符型指针所对应的开辟的空间释放掉, 此时该字符型指针成为了野指针, 故置为空指针
//再把长度len和容量alloc置为0
void strbuf_release(struct strbuf * sb)
{
    free(sb->buf);
    sb->buf = NULL;

    sb->len = 0;
    sb->alloc = 0;
}

//通过两个缓冲区指针a、b, 交换两个缓冲区sb_a、sb_b
void strbuf_swap(struct strbuf * a, struct strbuf * b)
{
    struct strbuf* temp;

    temp = b;

    *b = *a;

    *a = *temp;

}

//将缓冲区sb中的原始内容, 即字符型指针取出, 并设置缓冲区sb为空, 即让现在缓冲区sb存储的字符型指针为空指针, 长度和容量都为0
char * strbuf_detach(struct strbuf * sb, size_t * sz)
{
    char * content;

    content = sb->buf;

    sb->buf = NULL;

    sb->len = 0;
    sb->alloc = 0;

    return content;
}

//比较两个缓冲区sb中的内容是否相同：先比较是否等长, 等长的话再用strcmp比较, 返回值为0说明内容相同（内容相同即可, 不考虑容量alloc是否相等）
int strbuf_cmp(const struct strbuf * first, const struct strbuf * second)
{
    if (first->len != second->len)
    {
        return -1;
    }

    return strcmp(first->buf, second->buf);
}

//清空缓冲区sb：和释放缓冲区sb的区别是, 此时缓冲区sb的容量保持不变, 但是清空内容, 即让长度为0, 且让字符串的内容被截断
void strbuf_reset(struct strbuf * sb)
{
    sb->len = 0;

    sb->buf[0] = '\0';
}

//Part 2B

//确保在缓冲区sb中, 除了字符串已经占据的空间大小len + 1, 还有extra个字节的空闲空间
//先计算将容量扩容到2倍后的新容量, 再计算已占据的空间大小和extra个字节共需要多少空间, 前者更大则依据前者扩容, 后者更大则依据后者扩容（刚刚好）
void strbuf_grow(struct strbuf * sb, size_t extra)

//向缓冲区sb中添加长度为len的数据, 数据指针为data
void strbuf_add(struct strbuf * sb, const void * data, size_t len)

//向缓冲区sb中添加一个字符c
void strbuf_addch(struct strbuf * sb, int c)

//向缓冲区sb中添加一个字符串s
void strbuf_addstr(struct strbuf * sb, const char * s)

//向缓冲区sb中添加另一个缓冲区的数据
void strbuf_addbuf(struct strbuf * sb, const struct strbuf * sb2)

//设置缓冲区sb的长度len
void strbuf_setlen(struct strbuf * sb, size_t len)

//计算缓冲区sb中, 目前仍可以向后添加多少个字符
size_t strbuf_avail(const struct strbuf * sb)

//向缓冲区sb中, 内存坐标为pos的位置, 插入长度为len的数据
void strbuf_insert(struct strbuf * sb, size_t pos, const void * data, size_t len)

