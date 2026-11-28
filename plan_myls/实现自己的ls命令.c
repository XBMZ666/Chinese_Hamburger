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






//定义结构体类型PrintWidths：用于保存打印输出时各内容的对应宽度
typedef struct
{
    int inode_width;     //inode编号列所需的宽度
    int block_width;     //磁盘块数列所需的宽度
    int link_width;      //硬链接数列所需的宽度
    int user_width;      //用户名列所需的宽度
    int group_width;     //用户组列所需的宽度
    int size_width;      //文件大小列所需的宽度
}PrintWidths;






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






//定义函数calculate_widths：扫描文件列表, 并计算各列在打印输出时的宽度
PrintWidths calculate_widths(const FileList * list)
{
    PrintWidths widths = {0, 0, 0, 0, 0, 0};

    char number_buffer[32];

    int current = 0;
    //某一种列的所需宽度, 取在文件列表中, 所有文件该列的最大宽度
    for (int index = 0; index < list->count; index++)       //遍历文件列表中的每一个文件
    {
        const FileItem * item = &list->items[index];

        current = number_width(item->info.st_ino);
        if (current > widths.inode_width)
        {
            widths.inode_width = current;
        }

        current = number_width(item->info.st_blocks / 2);
        if (current > widths.block_width)
        {
            widths.block_width = current;
        }

        current = number_width(item->info.st_nlink);
        if (current > widths.link_width)
        {
            widths.link_width = current;
        }

        current = strlen(get_user_name(item->info.st_uid, number_buffer));
        if (current > widths.user_width)
        {
            widths.user_width = current;
        }

        current = strlen(get_group_name(item->info.st_gid, number_buffer));
        if (current > widths.group_width)
        {
            widths.group_width = current;
        }

        current = number_width(item->info.st_size);
        if (current > widths.size_width)
        {
            widths.size_width = current;
        }

    }

    return widths;
}





//定义函数make_mode_string：把权限字符串化
void make_mode_string(mode_t mode, char text[11])
{
    const char * permission_chars = "rwxrwxrwx";

    if (S_ISDIR(mode))
    {
        text[0] = 'd';
    }

    else if (S_ISLNK(mode))
    {
        text[0] = 'l';
    }

    else if (S_ISCHR(mode))
    {
        text[0] = 'c';
    }

    else if (S_ISBLK(mode))
    {
        text[0] = 'b';
    }

    else if (S_ISFIFO(mode))
    {
        text[0] = 'p';
    }

    else if (S_ISSOCK(mode))
    {
        text[0] = 's';
    }

    else
    {
        text[0] = '-';
    }

    for (int index = 1; index <= 9; index++)
    {
        text[index] = '-';      //每个权限初始化为关闭状态

        //这里的1视作0000000000000001, 1用于表示所在数位对应的位置的权限开启
        //比如index的值为1时, 则把1左移8个二进制位得到100000000
        //比如index的值为3时, 则把1左移5个二进制位得到000100000
        //mode的二进制表示中, 权限部分刚好是从最低位起计数, 总共9个二进制位. 如：110100100
        if (mode & (1 << (9 - index)))       
        {
            text[index] = permission_chars[index - 1];
        }
    }

    if (mode & S_ISUID)
    {
        if (text[3] == 'x')
        {
            text[3] = 's';
        }

        else
        {
            text[3] = 'S';
        }
    }

    if (mode & S_ISGID)
    {
        if (text[6] == 'x')
        {
            text[6] = 's';
        }

        else
        {
            text[6] = 'S';
        }
    }

    if (mode & S_ISVTX)
    {
        if (text[9] == 'x')
        {
            text[9] = 't';
        }

        else
        {
            text[9] = 'T';
        }
    }

    text[10] = '\0';

    return;
}





//定义函数make_time_string：把修改时间转换为ls风格
void make_time_string(time_t file_time, char buffer[32])
{
    time_t now = time(NULL);       //获取当前时间

    struct tm * time_info = localtime(&file_time);       //转换为本地时间的年月日时分秒
    if (time_info == NULL)
    {
        snprintf(buffer, 32, "未知时间");

        return;
    }

    if (now - file_time >15552000 || file_time > now + 3600)
    {
        strftime(buffer, 32, "%b %e  %Y", time_info);
    }

    else
    {
        strftime(buffer, 32, "%b %e %H:%M", time_info);
    }

    return;
}






//定义函数print_long_info：打印输出文件名之前的详细信息
void print_long_info(const FileItem * item, const PrintWidths * widths)
{
    char mode_text[11];
    char user_buffer[32];
    char group_buffer[32];
    char time_text[32];
    const char * user_name;
    const char * group_name;

    make_mode_string(item->info.st_mode, mode_text);
    make_time_String(item->info.st_mtime, time_text);

    user_name = get_user_name(item->info.st_uid, user_buffer);
    group_name = get_group_name(item->info.st_gid, group_buffer);

    printf("%s %*d ", mode_text, widths->link_width, item->info.st_nlink);
    printf("%-*s %-*s ", widths->user_width, user_name, widths->group_width, group_name);
    printf("%*d %s ", widths->size_width, item->info.st_size, time_text);

    return;
}






//定义函数print_item：打印输出一项
void print_item(const FileItem * item, const Options * options, const PrintWidths * widths)
{

    return;
}






//定义函数print_items：打印输出整个文件列表
void print_items(const FileList * list, const Options * options)
{
    
    return;
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


