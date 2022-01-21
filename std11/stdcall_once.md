# std::call_once

```cpp
{  static classname *Instance(bool create_if_needed = true) {              
    static classname *instance = nullptr;                                 
    if (!instance && create_if_needed) {                                  
      static std::once_flag flag;// 全局，静态                                   
      std::call_once(flag,                                                
                     [&] { instance = new (std::nothrow) classname(); }); 
    }                                                                     
    return instance;                                                      
  } 
  ```