

## 1 Cancelable Call
Using the return function to cancel fn in delay seconds.The return-function returns true means fn has been called, while returns false meas fn has been canceled.
```cpp
template <class Fn, class... Args>
std::function<bool()>
CancelableCall(uint32_t delay, Fn &&fn, Args &&...args)
{
  auto tmp = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);
  auto p_wait_send = std::make_shared<std::atomic<bool>>(true);
  auto p_delay_time = std::make_shared<uint32_t>(delay);
  auto p_mutex = std::make_shared<std::mutex>();
  auto p_cv = std::make_shared<std::condition_variable>();
  auto p_callbalie = std::make_shared<std::function<int()>>(tmp);
  auto func = [=](std::shared_ptr<uint32_t> p_delay_time,
                  std::shared_ptr<std::mutex> p_mutex,
                  std::shared_ptr<std::condition_variable> p_cv,
                  std::shared_ptr<std::function<int()>> p_callbalie) {
    std::unique_lock<std::mutex> lck(*p_mutex);
    int rc = p_cv->wait_for(lck, std::chrono::seconds(*p_delay_time),
                            [=]() { return *p_wait_send == false; });
    if (rc == 0) {
      p_wait_send->store(false);
      if ((*p_callbalie)()) {
        PRINTF("diag_send_event_stat() Fail\n");
      } else {
        PRINTF("diag_send_event_stat() Done\n");
      }
    } else {
    }
  };
  std::thread th_delay_call(func, p_delay_time, p_mutex, p_cv, p_callbalie);
  th_delay_call.detach();
  return [=]() -> bool {
    if (p_wait_send->load() == true) {
      p_wait_send->store(false);
      p_cv->notify_all();
      return false;
    } else {
      return true;
    }
  };
}
```
## 2 Get json Config
When you want to get a single json config, you can call **GetJsonConfig(xxx.json,"password")**;then it will return you the root["password"].AsString();
```cpp
std::string GetJsonConfig(std::string json_path, std::string json_index) {
  Json::Value json_iter;
  Json::CharReaderBuilder json_builder;
  JSONCPP_STRING errs;
  std::stringstream ss(json_index);
  std::string iter_indx;
  std::ifstream file_stream(json_path.c_str(), std::ios::in);
  if (Json::parseFromStream(json_builder, file_stream, &json_iter, &errs)) {
    while (ss >> iter_indx) {
      json_iter = json_iter[iter_indx];
    }
    file_stream.close();
    return json_iter.asString();
  }
  file_stream.close();
  return "";
}
```