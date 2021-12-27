# Lambda
## 1 外部变量访问方式说明符
```cpp
auto f = [a] (int)->void { cout << a << endl; return;};
``` 

Lambda参数表：
|||||
|:-:|:-:|:-:|:-:|
|[=]|[&]|[a]|[&a]
|全部值传递|全部值引用|a的值传递|a的值引用
||


