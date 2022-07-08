/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <iostream>
#include "boost/optional.hpp"
#include "boost/variant.hpp"
#include "core/instance_specifier.h"
#include "core/result.h"
#include "core/vector.h"
#include "example/example.h"
#include "example/example_error_domain.h"

int main(int argc, char **argv) {
  std::cout << "Running example" << std::endl;
  hra::core::StringView node_path("example/sample_node1");
  hra::core::InstanceSpecifier inst_spec =
      hra::core::InstanceSpecifier::Create(node_path).Value();

  hra::core::Example e;
  hra::core::Result<void> res1 = e.Open(inst_spec);
  if (!res1.HasValue()) {
    std::cout << "Example open failed, errorcode is " << res1.Error().Value()
              << std::endl;
  }

  hra::core::Result<int> res2 = e.GetNumber(10);
  if (res2.HasValue()) {
    std::cout << "Get number: " << res2.Value() << std::endl;
  } else {
    std::cout << "Get number failed, errorcode is " << res2.Error().Value()
              << std::endl;
  }

  hra::core::Result<std::string> res3 = e.GetString(-1);
  if (res3.HasValue()) {
    std::cout << "Get string: " << res3.Value() << std::endl;
  } else {
    std::cout << "Get string failed, errorcode is " << res3.Error().Value()
              << std::endl;
  }

  using IntFloatString = boost::variant<int, float, std::string>;
  IntFloatString i = 100;
  std::cout << boost::get<int>(i) << std::endl;

  boost::optional<int> value = 10;
  std::cout << value.value() << std::endl;

  hra::core::Vector<int> vec;
  vec.push_back(13);
  vec.push_back(2);
  std::cout << vec[0] << std::endl;

  hra::core::Result<std::string> result1 =
      hra::core::Result<std::string>::FromValue("abcdefg");
  hra::core::Result<std::string> result2 =
      hra::core::Result<std::string>::FromValue("hijk");
  if (result1 != result2) {
    std::cout << "!=" << std::endl;
  } else {
    std::cout << "==" << std::endl;
  }
  result1 = hra::core::Result<std::string>(
      MakeErrorCode(hra::core::ExampleErrc::kInvalidInputNumber));
  std::cout << result1.HasValue() << std::endl;
  return 0;
}
