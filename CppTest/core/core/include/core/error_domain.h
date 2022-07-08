/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>

namespace hra {
namespace core {

class ErrorCode;

class ErrorDomain {
 public:
  using IdType = std::uint64_t;
  using CodeType = std::int32_t;
  using SupportDataType = std::int32_t;

  ErrorDomain(const ErrorDomain &) = delete;

  // Copy assignment shall be disabled.
  ErrorDomain &operator=(const ErrorDomain &) = delete;

  ErrorDomain(ErrorDomain &&) = delete;

  // Move assignment shall be disabled.
  ErrorDomain &operator=(ErrorDomain &&) = delete;

  // Compare for equality with another ErrorDomain instance.
  constexpr bool operator==(const ErrorDomain &other) const noexcept {
    return id_ == other.id_;
  }

  // Compare for non-equality with another ErrorDomain instance.
  constexpr bool operator!=(const ErrorDomain &other) const noexcept {
    return id_ != other.id_;
  }

  // Return the unique domain identifier.
  constexpr IdType Id() const noexcept { return id_; }

  // Return the name of this error domain.
  virtual const char *Name() const noexcept = 0;

  // Return a textual representation of the given error code.
  virtual const char *Message(CodeType code_type) const noexcept = 0;

 protected:
  explicit constexpr ErrorDomain(IdType id) noexcept : id_(id) {}

  ~ErrorDomain() = default;

 private:
  IdType const id_;
};

}  // namespace core
}  // namespace hra
