/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <algorithm>
#include <string>
#include "core/core_error_demain.h"
#include "core/result.h"
#include "core/string_view.h"

namespace hra {
namespace core {

// An shortname-path wrapper
class InstanceSpecifier final {
 public:
  // Lifetime of underlying string has to exceed the lifetime of the constructed
  // InstanceSpecifier.
  explicit InstanceSpecifier(StringView meta_model_identifier)
      :  // meta_model_identifier
        meta_model_id_(meta_model_identifier.data()) {}

  InstanceSpecifier(const InstanceSpecifier &other) {
    meta_model_id_ = other.meta_model_id_;
  }

  InstanceSpecifier(InstanceSpecifier &&other) noexcept {
    meta_model_id_ = other.meta_model_id_;
    other.meta_model_id_ = other.meta_model_id_.substr(0, 0);
  }

  InstanceSpecifier &operator=(const InstanceSpecifier &other) {
    if (this != &other) {
      meta_model_id_ = other.meta_model_id_;
    }
    return *this;
  }

  InstanceSpecifier &operator=(InstanceSpecifier &&other) {
    if (this != &other) {
      meta_model_id_ = other.meta_model_id_;
      other.meta_model_id_ = other.meta_model_id_.substr(0, 0);
    }
    return *this;
  }

  ~InstanceSpecifier() noexcept {}

  // Create a new instance of this class.
  static Result<InstanceSpecifier> Create(StringView meta_model_identifier) {
    size_t end_offset = -1;
    static CoreErrorDomain domain;
    do {
      size_t const cur_offset = end_offset + 1;  // skip the '/'
      end_offset = meta_model_identifier.find("/", cur_offset);
      size_t const len = (end_offset == StringView::npos)
                             ? StringView::npos
                             : end_offset - cur_offset;
      StringView const sub_path = meta_model_identifier.substr(cur_offset, len);

      if (sub_path.empty()) {
        return Result<InstanceSpecifier>::FromError(
            MakeErrorCode(CoreErrc::kInvalidMetaModelPath));
      }
      if (!IsValidMetamodelIdentifierPart(sub_path)) {
        return Result<InstanceSpecifier>::FromError(
            MakeErrorCode(CoreErrc::kInvalidMetaModelShortname));
      }
    } while (end_offset != StringView::npos);
    InstanceSpecifier inst_spec(meta_model_identifier);
    return Result<InstanceSpecifier>(inst_spec);
  }
  // eq operator to compare with other InstanceSpecifier instance.
  bool operator==(const InstanceSpecifier &other) const noexcept {
    return meta_model_id_ == other.ToString();
  }

  bool operator==(StringView other) const noexcept {
    return meta_model_id_ == other;
  }
  // uneq operator to compare with other InstanceSpecifier instance.
  bool operator!=(const InstanceSpecifier &other) const noexcept {
    return meta_model_id_ != other.meta_model_id_;
  }
  // uneq operator to compare with other InstanceSpecifier string
  // representation.
  bool operator!=(StringView other) const noexcept {
    return meta_model_id_ != other;
  }
  // lower than operator to compare with other InstanceSpecifier for ordering
  // purposes
  bool operator<(const InstanceSpecifier &other) const noexcept {
    return meta_model_id_ < other.ToString();
  }
  /**
   * @brief return the stringified form of InstanceSpecifier
   * @return stringified form of InstanceSpecifier. Lifetime of the underlying
   * string is only guaranteed for the lifetime of the underlying string of the
   * StringView passed to the constructor.
   */
  StringView ToString() const noexcept { return meta_model_id_; }

 private:
  constexpr static bool IsValidStartChar(char ch) noexcept {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
  }

  constexpr static bool IsValidChar(char ch) noexcept {
    return IsValidStartChar(ch) || (ch >= '0' && ch <= '9') || (ch == '_');
  }

  static bool IsValidMetamodelIdentifierPart(StringView text) noexcept {
    if (text.empty()) {
      return false;
    }
    return IsValidStartChar(text[0]) &&
           std::all_of(text.begin() + 1, text.end(), IsValidChar);
  }

  std::string meta_model_id_;
};

static bool operator==(StringView lhs, const InstanceSpecifier &rhs) noexcept {
  return lhs == rhs.ToString();
}

static bool operator!=(StringView lhs, const InstanceSpecifier &rhs) noexcept {
  return lhs != rhs.ToString();
}

}  // namespace core
}  // namespace hra
