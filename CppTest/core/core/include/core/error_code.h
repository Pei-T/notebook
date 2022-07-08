/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "core/error_domain.h"
#include "core/string_view.h"

namespace hra {
namespace core {

class ErrorCode final {
 public:
  /**
   * @brief Construct a new ErrorCode instance with parameters.
   * Parameters (in):
   * value: a domain-specific error code value
   * domain: the ErrorDomain associated with value
   * data: optional vendor-specific supplementary error context data
   */
  constexpr ErrorCode(ErrorDomain::CodeType value, const ErrorDomain &domain,
                      ErrorDomain::SupportDataType data =
                          ErrorDomain::SupportDataType()) noexcept
      : value_(value), data_type_(data), domain_(&domain) {}

  // Return the raw error code value
  constexpr ErrorDomain::CodeType Value() const noexcept { return value_; }

  // Return the domain with which this ErrorCode is associated.
  constexpr const ErrorDomain *Domain() const noexcept { return domain_; }

  // Return the supplementary error context data.
  constexpr ErrorDomain::SupportDataType SupportData() const noexcept {
    return data_type_;
  }

  // Return a textual representation of this ErrorCode.
  StringView Message() const noexcept { return Domain()->Message(Value()); }

 private:
  ErrorDomain::CodeType value_;
  ErrorDomain::SupportDataType data_type_;
  ErrorDomain const *domain_;
};

// Two ErrorCode instances compare equal if the results of their Value() and
// Domain() functions are equal. Return value: rue if the two instances compare
// equal, false otherwise
constexpr bool operator==(const ErrorCode &lhs, const ErrorCode &rhs) noexcept {
  return *lhs.Domain() == *rhs.Domain() && lhs.Value() == rhs.Value();
}

// Return value: true if the two instances compare not equal, false otherwise
constexpr bool operator!=(const ErrorCode &lhs, const ErrorCode &rhs) noexcept {
  return *lhs.Domain() != *rhs.Domain() || lhs.Value() != rhs.Value();
}

}  // namespace core
}  // namespace hra
