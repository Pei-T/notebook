/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <string>
#include "core/instance_specifier.h"

namespace hra {
namespace core {

/**
 * @brief Core example project
 *
 */
class Example final {
 public:
  Example() {}
  ~Example() {}

  /**
   * @brief Example open method
   *
   * @param inst_spec
   * @return Result<void>
   */
  Result<void> Open(const hra::core::InstanceSpecifier &inst_spec);
  /**
   * @brief Example Get number
   *
   * @param intput_num
   * @return Result<int>
   */
  Result<int> GetNumber(int intput_num);

  /**
   * @brief Get the String object
   *
   * @param input
   * @return Result<std::string>
   */
  Result<std::string> GetString(int input);
};

}  // namespace core
}  // namespace hra
