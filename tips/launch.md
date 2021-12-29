# 远程Debug json文件

## 1 前提
Ubuntu系统，且改系统与板子能ping通。
## 2 json
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program":  "可执行文件或动态库",
            "args": [],
            "stopAtEntry": false,
            "cwd":      "源码目录",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "gdb 目录",
            "miDebuggerServerAddress": "板子IP:板子端口",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
// gdbserver 192.168.2.10:9900 ./xxx
```