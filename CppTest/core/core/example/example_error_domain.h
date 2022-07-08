/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "core/error_code.h"
#include "core/error_domain.h"

namespace hra {
namespace core {

enum class ExampleErrc : ErrorDomain::CodeType {
  kInvalidInstanceSpecifier = 1,
  kInvalidInputNumber
};

class ExampleErrorDomain final : public ErrorDomain {
 public:
  ExampleErrorDomain() : ErrorDomain(domain_id_) {}

  const char *Name() const noexcept override { return "Core"; }

  const char *Message(CodeType code_type) const noexcept override {
    ExampleErrc code = static_cast<ExampleErrc>(code_type);
    switch (code) {
      case ExampleErrc::kInvalidInstanceSpecifier:
        return "Not a valid instance specifier";
      case ExampleErrc::kInvalidInputNumber:
        return "Invalid input number";
      default:
        return "Unknown error";
    }
  }

 private:
  constexpr static IdType domain_id_ = 0x20000000;
};

static ExampleErrorDomain example_domain;

constexpr const hra::core::ErrorDomain &GetExampleErrorDomain() noexcept {
  return example_domain;
}

constexpr hra::core::ErrorCode MakeErrorCode(
    ExampleErrc err_code, hra::core::ErrorDomain::SupportDataType data =
                              ErrorDomain::SupportDataType()) noexcept {
  return hra::core::ErrorCode(static_cast<ErrorDomain::CodeType>(err_code),
                              example_domain);
}

}  // namespace core
}  // namespace hra
