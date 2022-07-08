# Constructor

一个class有6个构造函数，以下将列举6中构造函数。
```cpp
class Test{
  public:
    // 左值构造函数
    Test(const int &value):x(value){}
    // 右值构造函数
    Test(int &&value):x(std::move(value)){}
    // 左值复制构造
    Test(const Test &other):x(other.x){}
    //


  private:
    int x;

};


```