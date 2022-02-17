```
package tutorial;

message Persion {
    required string name = 1;   
    required int32 age = 2;
}

message AddressBook {
    repeated Persion persion = 1;
}
```

```
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto
示例中执行命令
protoc --cpp_out=/tmp addressbook.proto 
会在/tmp中生成文件addressbook.pb.h和addressbook.pb.cc。
```