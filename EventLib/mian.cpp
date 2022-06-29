#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <unordered_map>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName &) = delete;     \
  void operator=(const TypeName &) = delete

#define DECLARE_SINGLETON(classname)                                      \
 public:                                                                  \
  static classname *Instance(bool create_if_needed = true) {              \
    static classname *instance = nullptr;                                 \
    if (!instance && create_if_needed) {                                  \
      static std::once_flag flag;                                         \
      std::call_once(flag,                                                \
                     [&] { instance = new (std::nothrow) classname(); }); \
    }                                                                     \
    return instance;                                                      \
  }                                                                       \
                                                                          \
 private:                                                                 \
  DISALLOW_COPY_AND_ASSIGN(classname)

class Task {
 public:
  Task(){};
  virtual ~Task(){};
  virtual int TaskFunc(void *) { return 0; }
};

class SourceTaskGallery {
  DECLARE_SINGLETON(SourceTaskGallery);

 public:
  SourceTaskGallery() {}
  void SetTask(uint32_t id, Task &&task) {
    task_map_.insert(std::pair(id, task));
  }
  Task &GetTask(uint32_t id) { return task_map_[id]; }
  void EraseTask(uint32_t id) { task_map_.erase(task_map_.find(id)); }

 private:
  std::unordered_map<uint32_t, Task> task_map_;
};

class TaskQueue {
 private:
  std::queue<std::packaged_task<int()>> task_queue_;
};

class ThreadPoll {};
