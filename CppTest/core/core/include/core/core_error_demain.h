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

enum class CoreErrc : ErrorDomain::CodeType {
  invalid_args = 1,
  kInvalidMetaModelShortname,
  kInvalidMetaModelPath
};

class CoreErrorDomain final : public ErrorDomain {
 public:
  CoreErrorDomain() : ErrorDomain(domain_id_) {}

  const char *Name() const noexcept override { return "Core"; }

  const char *Message(CodeType code_type) const noexcept override {
    CoreErrc code = static_cast<CoreErrc>(code_type);
    switch (code) {
      case CoreErrc::invalid_args:
        return "Invalid argument";
      case CoreErrc::kInvalidMetaModelShortname:
        return "Invalid meta model shortname";
      case CoreErrc::kInvalidMetaModelPath:
        return "Invalid meta model path";
      default:
        return "Unknown error";
    }
  }

 private:
  constexpr static IdType domain_id_ = 0x10000000;
};

static CoreErrorDomain core_domain;

constexpr const hra::core::ErrorDomain &GetCoreErrorDomain() noexcept {
  return core_domain;
}

constexpr hra::core::ErrorCode MakeErrorCode(
    CoreErrc err_code, hra::core::ErrorDomain::SupportDataType data =
                           ErrorDomain::SupportDataType()) noexcept {
  return hra::core::ErrorCode(static_cast<ErrorDomain::CodeType>(err_code),
                              core_domain);
}

}  // namespace core
}  // namespace hra
