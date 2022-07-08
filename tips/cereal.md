使用cereal序列化，反序列化。
``` cpp
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <iostream>
#include <string>
using namespace std;
struct MySubClass {
  string source;
  string target;
  template <class Archive>
  void serialize(Archive& archive) {
    archive(CEREAL_NVP(source), CEREAL_NVP(target));
  }
};

struct MyClass {
  char x, y, z;
  string name;
  vector<int> data;
  MySubClass sub;
  template <class Archive>
  void serialize(Archive& archive) {
    archive(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z), CEREAL_NVP(name),
            CEREAL_NVP(data), CEREAL_NVP(sub));
  }
};

int main() {
  MyClass data{1, 2, 3, "adas", {3, 4, 5, 6}, {"local", "centre"}};
  std::ostringstream os(std::stringstream::binary);
  {
    cereal::JSONOutputArchive out_archive(os);  // Create an output archive
    out_archive(CEREAL_NVP(data));
  }
  string json_str = os.str();
  cout << json_str << endl;

  std::stringstream is(json_str);
  MyClass data_new;
  {
    cereal::JSONInputArchive archive_in(is);
    archive_in(data_new);
    cout << data_new.sub.source << endl;
  }
}
```