
```cpp
  bool operator()(T send_msg){
      return true;
  }
```
```cpp
	MyStr& operator=(const MyStr& str) {
		cout << "operator=" << endl;
		if (this != &str) {
				this->id = str.id;
				this->name = str.name;
		}
	return *this;
	}

```
```cpp
bool operator==(const Person& other)
	{
		std::cout << "call member function operator==" << std::endl;
		if (this->m_age == other.m_age)
		{
			return true;
		}
		return false;
	}
```