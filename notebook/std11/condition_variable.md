# condition_variable
## 1 Brief introduction
```cpp
#include <condition_variable>
std::condition_variable cv;
std::mutex mtx;

std::unique_lock<std::mutex> lck(mtx);

cv.wait(lck,[]()->bool{});

state = cv.wait_for(lck,std::chrono::second(1),[]()->bool{})
if(state)
    Func();
else 
    TimeoverFunc();

cv.notify_all()
```