# OS
## 1 os.path
```py
import os
# python中os.path常用模块
# os.path.sep:路径分隔符      linux下就用这个了’/’
# os.path.altsep: 根目录
# os.path.curdir:当前目录
# os.path.pardir：父目录
# os.path.abspath(path)：绝对路径
# os.path.join():       常用来链接路径
# os.path.split(path):      把path分为目录和文件两个部分，以列表返回
print (os.path.split('/root/pp/f.c'))
# ('/root/pp', 'f.c')
```