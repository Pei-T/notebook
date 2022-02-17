
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