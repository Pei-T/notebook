# shell

## 1 Args and Argv in Script
```sh
# args num $#
if [ $# == 1 ];then
    sorce_file="all"
    echo $1
elif [ $# == 2 ];then
    echo $1
    echo $2
fi
```
# 2 Check ENV
```sh
if [ ${CROSS_COMPILE} ];then
    echo ${CROSS_COMPILE}g++
else
    current_path=$(pwd)
    cd /home/tangpei/sysmgr/autoMaster/build
    source envsetup.sh
    lunch 6
    cd ${current_path}
    echo ${current_path}
    echo ${CROSS_COMPILE}g++
fi
```

## 3 Get CMD Result
```sh
    current_path=$(pwd)
    echo ${current_path}
```
## 4 Check String in CMD Result
```sh
cat /etc/ld.so.conf|grep /lib/sensorlib|wc -l
```

## 5 Function
```sh
selectProjectType(){
    echo "请选择项目类型:"
    echo "1、test"
    echo "2、super parking"
    echo "3、super drive"
    echo "回车、使用cmakelist里面的项目类型"
    echo "请输入1-3中的任意整数或者直接回车:"
    while true
    do
        read PROJECT_TYPE_NUMBER
        if [ "$PROJECT_TYPE_NUMBER" == "" ];then
            PROJECT_TYPE_NUMBER=99
            break
        elif (( $PROJECT_TYPE_NUMBER > 0 && $PROJECT_TYPE_NUMBER < 3 ));then
            break
        else
            echo "请输入1-3中的任意整数或者直接回车:"
        fi
    done
}
```
## 6 Check Files

```sh
if [-f /bin/sysmgr];then
echo file_exist
fi

if [ -d /userdata/peiT ]; then
    echo file_exist
else
    mkdir peiT
fi
```

## 7 Run cmd in ssh
```sh
    ssh tangpei@10.97.100.38 -t '
        cd /home/tangpei/sysmgr/src/sys-mgr
        bash scopy.sh 
    '
```

## 8 Check Cmd lines

```sh
ps|grep local_sysmgr|wc -l
# result should sub one;
procrank|grep local_sysmgr|wc -l
# result should not sub one;
```
