# std::future
头文件：Defined in header <future>  
定义
```c++
template< class T > class future;  
template< class T > class future<T&>;  
template<> class future<void>;
```
## 1 成员函数：
|||
|---|---
|T get()| 阻塞，获取运行结果
|std::future_status wait|阻塞，直到可获取结果
|std::future_status wait_for(std::chrono::second(1))| 等待一定时间，返回完成，超时，错误。
|||

wait()返回结果
|||  
|---|---|
|std::future_status::ready|可以读结果
|std::future_status::timeout|超时
|std::future_status::deferred|出错
|||
## 2 例子
### 2.1 获取async结果
```c++
// STLasync.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>using namespace std::chrono;
std::string fetchDataFromDB(std::string recvData)
{
    std::cout << "fetchDataFromDB start" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(seconds(5));
    return "DB_" + recvData;
}

int main()
{

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
### 2.2 获取thread结果
```c++
#include <iostream>       
#include <functional>     
#include <thread>        
#include <future>     // std::promise, std::future

void print_int(std::future<int>& fut) {
    int x = fut.get();                    // 获取共享状态的值.
    std::cout << "value: " << x << '\n';  // 打印 value: 10.
}

int main ()
{
    std::promise<int> prom;                    // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future();  // 和 future 关联.
    std::thread t(print_int, std::ref(fut));   // 将 future 交给另外一个线程t.
    prom.set_value(10);                        // 设置共享状态的值, 此处和线程t保持同步.
    t.join();
    return 0;
}
```