# 实现自己的ls命令

## 任务说明
`ls`是 GNU/Linux 操作系统中常见的命令. 请使用 C 语言, 基于 GNU/Linux 操作系统, 编程实现`ls`命令的部分功能.

## 验收要求
* 实现`ls`的 -a、-l、-R、-t、-r、-i、-s 参数, 并允许这些参数任意组合.
* -R 需要对 / 的遍历测试.
* 界面美观（输出对齐、带颜色显示等）.
* 无资源与内存泄漏.
* 开发过程记录、总结并发布在个人博客中.

## 命令输入示例
```bash
ls -a -l
ls -a /home
ls -alR /
ls -t
ls -ai -t /home
ls -i /home /etc
```

## 个人实现
### 头文件选取
* `stdio.h`\
可拆成**std + io**, 即**standard input output**. 标准输入输出头文件, 用于提供标准输入输出函数. 在本实现中, 主要用到了：
1. `printf`：将内容打印输出到屏幕上
2. `fprintf`：将内容输出到指定位置
3. `snprintf`：按照给定的格式来生成一个字符串, 并存入字符数组

* `string.h`\
用于提供字符串的处理工具. 在本实现中, 主要用到了：
1. `strlen`：计算字符串长度
2. `strcmp`：比较两个字符串
3. `strcpy`：用字符串来给某个字符数组“赋值”
4. `strerror`：把错误编号转换成文字

* `stdlib.h`\
可拆成**std + lib**, 即**standard library**. 标准函数库头文件, 用于提供标准常用工具. 在本实现中, 主要用到了：
1. `malloc`：申请一块内存\
`malloc(strlen(字符串) + 1)`：为字符串申请足够的空间, +1是为了让隐式的`'\0'`也存入
2. `realloc`：调整已经申请的内存大小
`realloc(先前申请的内存的地址, 新的容量 * 单个数据类型大小)`：
3. `free`：释放空闲且无用的内存

* `dirent.h`\
可拆成**dir + ent**, 即**directory entry**. 用于提供“读取目录中各项内容”这一功能. 在本实现中, 主要用到了：
1. 类型`DIR`：保存一个已打开的目录
2. 类型`struct dirent`：保存刚从某个目录中读取的某一项
3. `opendir`：打开目录
4. `readdir`：从目录中读取当前这一项, 并准备读取下一项
5. `closedir`：关闭目录

* `errno.h`\
即**error number**. 用于提供错误编号`errno`, 来配合`strerror`这个函数.

* `unistd.h`\
即**Unix standard**. 用于提供 Unix/Linux 常用系统操作说明. 在本实现中, 主要用到了：
* `readlink`：读出符号链接所指向的名字, 来配合`lstat`使用

* `sys/stat.h`\
即**system/status**. 用于查询、处理文件的状态信息. 在本实现中, 主要用到了：
1. 类型`struct stat`：保存文件的详细信息
2. `lstat`：查询文件的详细信息
3. `S_ISDIR`：判断文件类型
4. `S_IXUSR`：检查文件权限

* `sys/type.h`\
即**system/type**. 用于提供系统常用的变量类型. 在本实现中, 主要用到了：
1. 类型`uid_t`：用户编号类型
2. 类型`gid_t`：用户组编号类型
3. 类型`mode_t`：文件类型和权限类型
4. 类型`ssize_t`：`readlink`的读取结果的类型


