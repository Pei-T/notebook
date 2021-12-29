## Lambda
### 1 外部变量访问方式说明符
```cpp
auto f = [a] (int)->void { cout << a << endl; return;};
```

Lambda参数表：
|||||
|:-:|:-:|:-:|:-:|
|[=]|[&]|[a]|[&a]
|全部值传递|全部值引用|a的值传递|a的值引用


### 2 eg:

```cpp
std::thread(
        [](uint16_t event_id, std::unordered_map<uint16_t, ErrorMsg> *send_map,
           std::mutex *lock) {
          sleep(5);
          auto it = send_map->find(event_id);
          if (it != send_map->end()) {
            diag_send_event_stat(it->second.msg_prio, it->second.module_id,
                                 it->second.event_id, DIAG_EVENT_FAIL);
            lock->lock();
            send_map->erase(it);
            lock->unlock();
          }
        },
        event_id, &send_map, &lock);
```


