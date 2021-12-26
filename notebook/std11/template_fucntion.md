# Template function

## 1 Brief introduction
~~~cpp
template <class T>
void function(T args)

template<typename Head, typename... Tail>
void print(const T& firstArg, const Types&... args) {
	std::cout << firstArg << " " << sizeof...(args) << std::endl;
	print(args...);
}
~~~
