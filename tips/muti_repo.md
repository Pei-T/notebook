# 如何将本地 git 仓库同步推送到远程的 gitee 和 github 仓库
 

在进行下面的实验之前你需要先在 gitee 及 github 上分别创建一个仓库来同步你本地仓库中的内容。
并为这两个仓库添加好密钥（可以相同，参见[使用 ssh-key](ssh_gitee.md)），以便建立 SSH 连接来访问相应的远程仓库。
下面我们假设你所创建好的两个仓库分别为：
1. https://gitee.com/someone/some_repo.git
2. https://github.com/someone/some_repo.git

## 1 使用命令行工具

你可以使用 Win10 自带的 Windows PowerShell 或者 Visual Studio 自带的 Developer PowerShell.
打开 Developer PowerShell 有两种方式：
1. 点击菜单项 View，然后点击 Terminal
2. 点击菜单项 Tools，然后点击 Command Line，接着点击 Developer PowerShell

在命令行下进入要推送的本地仓库所在的文件夹
(如果你使用 Developer PowerShell 且当前 VS 所打开的文件夹就是本地仓库所在的位置, 则命令行下的路径自动进入要推送的本地仓库)。
输入命令 git status 查看一下当前的状态。

增加 gitee 及 github 远程仓库（需要将本地仓库推送到这两个仓库）
```shell
git remote add origin_gitee https://gitee.com/someone/some_repo.git
git remote add origin_github https://github.com/someone/some_repo.git
#ps: git remote rename xxx origin_gitee重命名远端名称
```
上面命令为本地仓库创建了两个到远程仓库的连接，名字分别为 origin_gitee 和 origin_github 
(你也可以取为其它名字, 但通常缺省的名称为 origin)。

当你完成本地的 commit 后你就可以向远程仓库 push 了。将本地当前分支推送到 gitee 上的 master 分支:
```shell
git push -u origin_gitee master
```
将本地当前分支推送到 github 上的 master 分支:
```shell
git push -u origin_github master
```

## 2 自动脚本
```sh
git add -A
git commit -m "defult"
git push -u origin_gitee master
git push -u origin_github master
```