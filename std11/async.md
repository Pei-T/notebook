# std::async
    头文件：#include <async>
    函数定义：
        模板：template <class Fn, class... Args>
        返回值：future <typename result_of<Fn(Args...)>::type> 
        参数：async(launch policy, Fn&& fn, Args&&...args);
```cpp
std::async(std::launch::async, func, "Data")
```
## 1.1 返回值 
    future <typename result_of<Fn(Args...)>::type> 
    可以使用get、wait、wait_for、wait_until等待执行结束，区别是get可以获得执行的结果。
* 如果选择异步执行策略，调用get时，如果异步执行没有结束，get会阻塞当前调用线程，直到异步执行结束并获得结果。如果异步执行已经结束，不等待获取执行结果；
* 如果选择同步执行策略，只有当调用get函数时，同步调用才真正执行，这也被称为函数调用被延迟。
* 返回值必须被接收才能启动线程执行。
## 1.2 参数 
    第一个参数决定异步执行还是同步执行
|||
|---|---
|std::launch::async| 调用时执行；
|std::launch::deferred|获取结果时执行；
|std::launch::async \| std::launch::deferred| 可以异步或是同步，取决于操作系统，我们无法控制；
|default|则相当于(3)。
||
第二个参数接收一个可调用对象(仿函数、lambda表达式、类成员函数、普通函数......)作为参数,并且异步或是同步执行他们。

## 1.3 例子
```cpp{.line-numbers}
// STLasync.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
using namespace std::chrono;
std::string fetchDataFromDB(std::string recvData) {
    std::cout << "fetchDataFromDB start" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(seconds(5));
    return "DB_" + recvData;
}

int main() {

    std::cout << "main start" << std::this_thread::get_id() << std::endl;
    //获取开始时间
    system_clock::time_point start = system_clock::now();
    std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");
    std::future_status status;
    std::string dbData;
    do
    {
        status = resultFromDB.wait_for(std::chrono::seconds(1));

        switch (status)
        {
        case std::future_status::ready:
            std::cout << "Ready..." << std::endl;
            //获取结果
            dbData = resultFromDB.get();
            std::cout << dbData << std::endl;
            break;
        case std::future_status::timeout:
            std::cout << "timeout..." << std::endl;
            break;
        case std::future_status::deferred:
            std::cout << "deferred..." << std::endl;
            break;
        default:
            break;
        }

    } while (status != std::future_status::ready);
    //获取结束时间
    auto end = system_clock::now();

    auto diff = duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Total Time taken= " << diff << "Seconds" << std::endl;

    return 0;
}
```
```cpp{.line-numbers}

auto _ = std::async(std::launch::async, [](){ 
    while(true) cout << "async thread" <<endl; 
});
文件：

  
如果从std :: async获取的std :: future未被移动或绑定   对于一个引用，std :: future的析构函数将阻塞   完整表达式结束，直到异步操作完成，   基本上制作以下同步代码：

     
std :: async（std :: launch :: async，[] {f（）;}）; //临时的dtor等待   for f（）std :: async（std :: launch :: async，[] {g（）;}）; //没有开始   直到f（）完成
```