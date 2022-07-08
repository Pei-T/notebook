/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "example/example.h"
#include <iostream>
#include "example/example_error_domain.h"

namespace hra {
namespace core {

Result<void> Example::Open(const hra::core::InstanceSpecifier &inst_spec) {
  hra::core::Result<void> result;
  if (inst_spec.ToString() == "example/sample_node1") {
    std::cout << "init instance node1 success" << std::endl;
  } else {
    result.EmplaceError(MakeErrorCode(ExampleErrc::kInvalidInputNumber));
  }
  return result;
}

Result<int> Example::GetNumber(int intput_num) {
  if (intput_num < 0) {
    return hra::core::Result<int>::FromError(
        MakeErrorCode(ExampleErrc::kInvalidInputNumber));
  }
  int output_num = (intput_num + 10) / 2;
  return hra::core::Result<int>::FromValue(output_num);
}

Result<std::string> Example::GetString(int input) {
  if (input < 0) {
    return hra::core::Result<std::string>::FromError(
        MakeErrorCode(ExampleErrc::kInvalidInputNumber));
  }
  return hra::core::Result<std::string>::FromValue("test");
}

}  // namespace core
}  // namespace hra
