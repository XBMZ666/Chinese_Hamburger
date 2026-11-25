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






//把文件名和其所在目录拼接在一起
char * make_path(const char * directory, const char * name)
{
    char * full_path;

    return full_path;
}






//解析命令行参数
int parse_options(int argc, char ** argv)
{

}






int main(int argc, char ** argv)
{
    Options opt = {0, 0, 0, 0, 0, 0, 0};

    return 0;
}


