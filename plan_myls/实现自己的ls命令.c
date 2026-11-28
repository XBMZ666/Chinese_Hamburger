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







//定义函数free_list：释放文件列表占用的所有动态内存
void free_list(FileList * list)
{
    for (int index = 0; index < list->count; index++)
    {
        free(list->items[index].name);
        free(list->items[index].path);
    }

    free(list->items);

    list->items = NULL;
    list->count = 0;
    list->capacity = 0;

    return;
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
            return 0;
        }

        list->items = new_items;
        list->capacity = new_capacity;
    }

    char * name_copy;
    name_copy = (char *)malloc(strlen(name) + 1);
    if (name_copy == NULL)
    {
        fprintf(stderr, "myls：内存不足！\n");

        return 0;
    }

    strcpy(name_copy, name);

    char * full_path;

    full_path = make_path(directory, name_copy);
    if (full_path == NULL)      //为完整路径申请内存失败, 此时仅仅为文件名的拷贝申请内存成功了, 则需要释放掉这部分内存以防内存泄漏
    {
        free(name_copy);
        fprintf(stderr, "myls：内存不足！\n");

        return 0;
    }

    if (lstat(full_path, &(list->items[list->count].info)) == -1)      //查询full_path这个位置的详细信息, 并把详细信息存入该文件对应的info
    {
        fprintf(stderr, "myls：无法访问'%s'：%s！\n", full_path, strerror(errno));
        
        free(name_copy);
        free(full_path);

        return 1;
    }

    list->items[list->count].name = name_copy;
    list->items[list->count].path = full_path;
    list->count++;

    return 1;
}






//定义函数read_directory：读取一个目录到文件列表
int read_directory(const char * path, int show_all, FileList * list)
{
    DIR * directory = opendir(path);

    struct dirent * entry;

    if (directory == NULL)
    {
        //目录打开失败
        return 0;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (!show_all && entry->d_name[0] == '.')      //不读取以.开头的隐藏文件时则跳过隐藏文件这一项
        {
            continue;
        }

        if (!add_item(list, path, entry->d_name))
        {
            //将目录中的某一项加入文件列表时, 出现了错误
            free_list(list);
            closedir(directory);
            
            return 0;
        }
    }

    closedir(directory);
    return 1;
}






//定义函数compare_items：比较两个文件
int compare_items(const FileItem * first, const FileItem * second, const Options * options)
{
    int result = 0;

    if (options->sort_by_time)
    {
        if (first->info.st_mtime > second->info.st_mtime)
        {
            //first的文件修改时间比second的文件修改时间新
            result = -1;
        }

        else if (first->info.st_mtime < second->info.st_mtime)
        {
            //first的文件修改时间比second的文件修改时间晚
            result = 1;
        }

        else
        {
            result = strcmp(first->name, second->name);
        }
    }

    else
    {
        //按字典序来比较first和second的文件名
        result = strcmp(first->name, second->name);
    }

    if (options->reverse)
    {
        return (-result);
    }

    return result;
}






//定义函数number_width：计算一个非负整数占用的字符数
int number_width(int number)
{
    int width = 1;       //数字0会占用1个字符
    while (number >= 10)
    {
        width++;

        number /= 10;
    }

    return width;
}






//定义函数get_user_name：由用户编号获取可显示的名称
const char * get_user_name(uid_t user_id, char buffer[32])
{
    struct passwd * user = getpwuid(user_id);
    if (user != NULL)
    {
        return user->pw_name;
    }

    //通过用户编号并未查询到用户信息
    snprintf(buffer, 32, "%d", user_id);       //把用户编号转换为字符串

    return buffer;
}






//定义函数get_group_name：由用户组编号获取可显示的名称
const char * get_group_name(gid_t group_id, char buffer[32])
{
    struct group * group = getgrgid(group_id);
    if (group != NULL)
    {
        return group->gr_name;
    }

    //通过用户组编号并未查询到用户组信息
    snprintf(buffer, 32, "%d", group_id);       //把用户组编号转换为字符串

    return buffer;
}






//定义函数sort_items：使用冒泡排序整理当前目录的文件
void sort_items(FileList * list, const Options * options)
{
    for (int outer = 0; outer < list->count - 1; outer++)
    {
        int change = 0;

        for (int inner = 0; inner < list->count - 1 - outer; inner++)
        {
            if (compare_items(&(list->items[inner]), &(list->items[inner + 1]), options) > 0)
            {
                change = 1;

                FileItem temporary;
                temporary = list->items[inner];

                list->items[inner] = list->items[inner + 1];
                list->items[inner + 1] = temporary; 
            }
        }

        if (!change)
        {
            break;
        }
    }
}






//定义函数parse_options：解析命令行参数
int parse_options(int argc, char ** argv, Options * options, int * first_path)
{
    int argv_index = 1;      //第1个命令行参数是程序名, 所以需要从第2个命令行参数开始解析, 其索引为1

    //为解析命令行参数的两个条件设定两个标记
    int flag_a = 0;
    int flag_b = 0;

    if (argv_index < argc)      //确认至少有两个命令行参数, 否则就是最简单的无参数的ls命令；若正常解析, 则保证在argv_index的值达到argc后停止解析（不再存在对应的命令行参数）
    {
        flag_a = 1;
    }

    if (argv[argv_index][0] == '-' && argv[argv_index][1] != '\0')      //确认正在解析的命令行参数是以-开头的, 且不是单独的-
    {
        flag_b = 1;
    }

    while (flag_a && flag_b)
    {
        if (strcmp(argv[argv_index], "--") == 0)      //--表示选项已经结束, 接下来的命令行参数是文件名
        {
            argv_index++;
            break;
        }

        int char_index = 1;      //所解析的命令行参数, 第1个字符为-, 则从第2个字符开始解析, 其索引为1
        while (argv[argv_index][char_index] != '\0')      //一直解析, 直至遇到所解析的命令行参数的最末（\0）为止
        {
            char option = 0;
            option = argv[argv_index][char_index];

            if (option == 'a')
            {
                options->show_all = 1;
            }

            else if (option == 'l')
            {
                options->long_format = 1;
            }

            else if (option == 'R')
            {
                options->recursive = 1;
            }

            else if (option == 't')
            {
                options->sort_by_time = 1;
            }

            else if (option == 'r')
            {
                options->reverse = 1;
            }

            else if (option == 'i')
            {
                options->show_inode = 1;
            }

            else if (option == 's')
            {
                options->show_blocks = 1;
            }

            else
            {

            }

            char_index++;
        }

        argv_index++;

        flag_a = 0;
        flag_b = 0;

        if (argv_index < argc)      //保证在argv_index的值达到argc后停止解析（不再存在对应的命令行参数）
        {
            flag_a = 1;
        }


        if (argv[argv_index][0] == '-' && argv[argv_index][1] != '\0')      //确认正在解析的命令行参数是以-开头的, 且不是单独的-
        {
            flag_b = 1;
        }
    }
    
    //此时索引可能无对应的命令行参数, 也可能对应的命令行参数为一个路径
    *first_path = argv_index;

    return 1;
}






int main(int argc, char ** argv)
{
    Options opt = {0, 0, 0, 0, 0, 0, 0};

    int first_path = 1;

    parse_options(argc, argv, &opt, &first_path);

    printf("%d %d %d", opt.show_all, opt.recursive, opt.show_inode);

    return 0;
}


