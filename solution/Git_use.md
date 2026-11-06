最近帮同学注册github并且进行了一系列操作, 发现把自己的来时路忘得七七八八了, 特此记录一下Git的使用流程.
1. Windows系统和Linux系统都是先要下载Git, 下载后, 在终端输入命令`git --version`, 查看是否下载成功.
2. 下载成功后, 需要首次配置身份, 好像不配置身份的话, 就克隆不了github上的仓库. 配置身份的命令：\
`git config --global user.name "你的名字"`\
`git config --global user.email "你的邮箱"`
3. 接下来该克隆远程仓库了, 命令为：`git clone https://github.com/用户名/仓库名`.\
还有一种SSH方式, 具体没试过, 命令为：`git clone git@github.com:user/repo.git`
4. Git的核心工作流程：\
Git有3个区域：工作区（你编辑的文件） ——> 暂存区 ——> 本地仓库.\
远程仓库是第4个位置.\
**注意每次使用以下命令前, 要先切换到仓库对应的本地目录下**\
①查看状态
* `git status` 查看哪些文件被修改或未跟踪
* `git diff` 查看未暂存的改动
* `git diff --staged` 查看已暂存的改动\
②修改文件并暂存
* `git add file.txt` 暂存单个文件
* `git add .` 暂存所有已发生的改动
* `git add -p` 交互式选择要暂存的片段（暂时不太懂）\
③提交
* `git commit -m "备注"`\
④推送到远程
* `git push`

---
未完待续……


