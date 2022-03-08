# thread
## 1 

## 2 Pass by reference
Same to std::bind, std::thread and std::bind use the same mechanism, we must use **std::ref** to wrap
```cpp
#include <iostream>
#include <thread>
#include <string>

int main(){
    std::string a("Hello");
    std::cout << "address = " << &a << "\n";
    std::thread t([](std::string& a){
            std::cout << "in thread address = " << &a << "\n";
        }, std::ref(a));
    t.join();
}
```
