# std::chrono
头文件：#include <chrono>  
空间：namespace std::chrono;
```cpp
std::this_thread::sleep_for(std::chrono::seconds(3));

auto start = std::chrono::high_resolution_clock::now();
// do something
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<int, std::milli> tm(end - start);
```
## 2.1 时间对照表
|std::second|std::milli|std::micro|std::nano|
|:---:|:---:|:---:|:---:|
|秒|毫秒|微秒|纳秒|

## 2.2 例子
### 2.2.1 计算时间差
```cpp
auto start = std::chrono::high_resolution_clock::now();
// do something
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<int, std::milli> tm = end - start;	// 毫秒
// std::chrono::duration<double, std::micro> tm = end - start; // 微秒
std::cout << "time: " << tm.count() << "ms" << std::endl;
```
### 2.2.2 自定义"天"  
    std::duration<std::uint32_t, std::ratio<3600 * 24>> day; 
ps:  
template <intmax_t N, intmax_t D = 1> class ratio;  

|ratio|means|
|---|---|
|ratio<3600*24, 1>|day|
|ratio<3600, 1>|hours|
|ratio<60, 1>|minutes|
|ratio<1, 1> |seconds|
|ratio<1, 1000>|microseconds|
|ratio<1, 1000000>|microseconds|
|ratio<1, 1000000000>|nanosecons|
        eg: std::second = ratio<1, 1>
### 2.2.3 线程休眠
```cpp
std::this_thread::sleep_for(std::chrono::seconds(3)); 
std::this_thread::sleep_for(std::chrono:: milliseconds (100));
std::this_thread::sleep_for(ratio<3600*24, 1>(1));
```