# OpenSource
## 1. JsonCpp
### install
```sh
sudo apt-get install libjsoncpp-dev
# /usr/include/jsoncpp/json
# /usr/lib/x86_64-linux-gnu/libjsoncpp.so.1.7.2
```
### example1:readFromStream
```cpp
#include "json/json.h"
#include <fstream>
#include <iostream>
/** \brief Parse from stream, collect comments and capture error info.
 * Example Usage:
 * $g++ readFromStream.cpp -ljsoncpp -std=c++11 -o readFromStream
 * $./readFromStream
 * // comment head
 * {
 *    // comment before
 *    "key" : "value"
 * }
 * // comment after
 * // comment tail
 */
int main(int argc, char* argv[]) {
  Json::Value root;
  std::ifstream ifs;
  ifs.open(argv[1]);

  Json::CharReaderBuilder builder;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    std::cout << errs << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << root << std::endl;
  return EXIT_SUCCESS;
}
```
### example2:readFromString
```cpp
#include "json/json.h"
#include <iostream>
#include <memory>
/**
 * \brief Parse a raw string into Value object using the CharReaderBuilder
 * class, or the legacy Reader class.
 * Example Usage:
 * $g++ readFromString.cpp -ljsoncpp -std=c++11 -o readFromString
 * $./readFromString
 * colin
 * 20
 */
int main() {
  const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
  const auto rawJsonLength = static_cast<int>(rawJson.length());
  constexpr bool shouldUseOldWay = false;
  JSONCPP_STRING err;
  Json::Value root;

  if (shouldUseOldWay) {
    Json::Reader reader;
    reader.parse(rawJson, root);
  } else {
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
                       &err)) {
      std::cout << "error" << std::endl;
      return EXIT_FAILURE;
    }
  }
  const std::string name = root["Name"].asString();
  const int age = root["Age"].asInt();

  std::cout << name << std::endl;
  std::cout << age << std::endl;
  return EXIT_SUCCESS;
}
```
### example3:streamWrite
```cpp
#include "json/json.h"
#include <iostream>
#include <memory>
/** \brief Write the Value object to a stream.
 * Example Usage:
 * $g++ streamWrite.cpp -ljsoncpp -std=c++11 -o streamWrite
 * $./streamWrite
 * {
 *     "Age" : 20,
 *     "Name" : "robin"
 * }
 */
int main() {
  Json::Value root;
  Json::StreamWriterBuilder builder;
  const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

  root["Name"] = "robin";
  root["Age"] = 20;
  writer->write(root, &std::cout);

  return EXIT_SUCCESS;
}
```
### example4:stringWrite
```cpp
#include "json/json.h"
#include <iostream>
/** \brief Write a Value object to a string.
 * Example Usage:
 * $g++ stringWrite.cpp -ljsoncpp -std=c++11 -o stringWrite
 * $./stringWrite
 * {
 *     "action" : "run",
 *     "data" :
 *     {
 *         "number" : 1
 *     }
 * }
 */
int main() {
  Json::Value root;
  Json::Value data;
  constexpr bool shouldUseOldWay = false;
  root["action"] = "run";
  data["number"] = 1;
  root["data"] = data;

  if (shouldUseOldWay) {
    Json::FastWriter writer;
    const std::string json_file = writer.write(root);
    std::cout << json_file << std::endl;
  } else {
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);
    std::cout << json_file << std::endl;
  }
  return EXIT_SUCCESS;
}
```

## 2. Zmq




