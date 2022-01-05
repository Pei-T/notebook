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
