#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) { return std::pow(x, y); }
template <class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> task_any(
    F&& f, Args&&... args) {
  // std::packaged_task<std::result_of<F>()> task(
  //     std::bind(std::forward<F>(f), std::forward<Args>(args)...));
  // auto res = task.get_future();
  // std::cout << "task_any:\t" << res.get() << '\n';
  // return res;
  using return_type = typename std::result_of<F(Args...)>::type;
  std::packaged_task<return_type()> task(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));
  auto res = task.get_future();
  // task();
  std::thread th(std::move(task));
  // std::cout << "task any:\t" << res.get() << std::endl;
  return res;
}

void task_lambda() {
  std::packaged_task<int(int, int)> task(
      [](int a, int b) { return std::pow(a, b); });
  std::future<int> result = task.get_future();

  task(2, 9);

  std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind() {
  std::packaged_task<int()> task(std::bind(f, 2, 11));
  std::future<int> result = task.get_future();

  task();

  std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread() {
  std::packaged_task<int(int, int)> task(f);
  std::future<int> result = task.get_future();

  std::thread task_td(std::move(task), 2, 10);
  task_td.join();

  std::cout << "task_thread:\t" << result.get() << '\n';
}

int main() {
  std::cout << "Task any:\t" << task_any(f, 2, 3).get() << std::endl;
  ;
  task_lambda();
  task_bind();
  task_thread();
}