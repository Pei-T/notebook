
```cpp
#include<memory>
share_ptr<T> p_t;//用于线程之间，直接传递对象，传值也没关系。
shared_ptr<string> p1 = make_shared<string>(10, '9');  
auto p_send_flag = std::make_shared<std::atomic<bool>>(true);
std::shared_ptr<std::atomic<bool>> p_send_flag(std::atomic<bool>(true));
std::shared_ptr<std::atomic<bool>> p_send_flag(true);
```