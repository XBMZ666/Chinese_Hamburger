#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>






//定义结构体类型Options：用于存储自定义ls命令的参数设置状态
//1表示设置, 0表示未设置
typedef struct
{
    int show_all;
    int long_format;
    int recursive;
    int sort_by_time;
    int reverse;
    int show_inode;
    int show_blocks;
}Options;






//定义结构体类型FileItem：用于存储单个文件的文件名、位置（路径）、详细信息
typedef struct 
{
    char * name;
    char * path;
    struct stat info;    
}FileItem;






//定义结构体类型FileList：用于存储多个文件, 为之设置了现有文件数量和总容量
typedef struct
{
    FileItem * items;
    int count;
    int capacity;
}FileList;






//定义函数make_path：把文件名和其所在目录拼接在一起, 获得文件的完整路径
char * make_path(const char * directory, const char * name)
{
    char * full_path;

    int need_slash = 0;
    //常规目录：非空, 并且不以/结尾
    //非常规目录：空目录、根目录/等以/结尾的目录
    //拼接文件名和常规目录时, 需要在之间添加一个斜杠/
    if (directory[0] != '\0' && directory[strlen(directory) - 1] != '/')
    {
        need_slash = 1;
    }

    int length = 0;      //拼接后的字符串总长度
    length = strlen(directory) + strlen(name) + need_slash + 1;

    full_path = (char *)malloc(length * sizeof(char));

    if (full_path == NULL)
    {
        return NULL;
    }

    if (directory[0] == '\0')
    {
        //目录为空时, 完整路径即文件名
        snprintf(full_path, length, "%s", name);
    }

    else if(need_slash != 0)
    {
        //目录非空, 而且需要在目录和文件名之间添加斜杠（即常规目录）
        snprintf(full_path, length, "%s/%s", directory, name);
    }

    else
    {
        //目录非空, 但是不用在目录和文件名之间添加斜杠（如根目录/）
        snprintf(full_path, length, "%s%s", directory, name);
    }

    return full_path;
}






//定义函数add_item：向文件列表中添加新的文件
int add_item(FileList * list, const char * directory, const char * name)
{
    FileItem * new_items;
    int new_capacity = 0;

    if (list->count == list->capacity)
    {
        if (list->capacity == 0)      //第一次添加文件时, 文件列表的容量和现有文件数量都为0
        {
            new_capacity = 16;
        }

        else      //文件列表已满
        {
            new_capacity = list->capacity * 2;
        }

        new_items = (FileItem *)realloc(list->items, new_capacity * sizeof(FileItem));
        if (new_items == NULL)
        {
            fprintf(stderr, "myls：内存不足！\n");
            return 1;
        }

        list->items = new_items;
        list->capacity = new_capacity;
    }

    char * name_copy;
    name_copy = (char *)malloc(strlen(name) + 1);
    if (name_copy == NULL)
    {
        fprintf(stderr, "myls：内存不足！\n");

        return 1;
    }

    strcpy(name_copy, name);

    char * full_path;

    full_path = make_path(directory, name_copy);
    if (full_path == NULL)      //为完整路径申请内存失败, 此时仅仅为文件名的拷贝申请内存成功了, 则需要释放掉这部分内存以防内存泄漏
    {
        free(name_copy);
        fprintf(stderr, "myls：内存不足！\n");

        return 1;
    }

    if (lstat(full_path, &(list->items[list->count].info)) == -1)      //查询full_path这个位置的详细信息, 并把详细信息存入该文件对应的info
    {
        fprintf(stderr, "myls：无法访问'%s'：%s！\n", full_path, strerror(errno));
        
        free(name_copy);
        free(full_path);

        return 0;
    }

    list->items[list->count].name = name_copy;
    list->items[list->count].path = full_path;
    list->count++;

    return 0;
}






//定义函数parse_options：解析命令行参数
int parse_options(int argc, char ** argv)
{

}






int main(int argc, char ** argv)
{
    Options opt = {0, 0, 0, 0, 0, 0, 0};

    return 0;
}


