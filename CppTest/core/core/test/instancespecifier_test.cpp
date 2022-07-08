/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <gtest/gtest.h>
#include "core/core_error_demain.h"
#include "core/instance_specifier.h"

TEST(InstanceSpecifierTest, Constructor) {
  const std::string c_meta_model_id("id");
  hra::core::InstanceSpecifier instanceSpecifier(c_meta_model_id);

  EXPECT_TRUE(instanceSpecifier.ToString() == c_meta_model_id);
}

TEST(InstanceSpecifierTest, Factory) {
  const std::string c_meta_model_id("id");
  hra::core::Result<hra::core::InstanceSpecifier> result =
      hra::core::InstanceSpecifier::Create(c_meta_model_id);

  EXPECT_TRUE(result.Value() == c_meta_model_id);
}

TEST(InstanceSpecifierTest, Create1) {
  hra::core::StringView is_path("RootNode/Subnode/endpoint");
  hra::core::InstanceSpecifier is_obj =
      hra::core::InstanceSpecifier::Create(is_path).Value();
  EXPECT_TRUE(is_obj.ToString() == is_path);
}

TEST(InstanceSpecifierTest, Create2) {
  hra::core::StringView is_path("RootNode/Subnode/endpoint0");
  hra::core::Result<hra::core::InstanceSpecifier> result =
      hra::core::InstanceSpecifier::Create(is_path);
  hra::core::InstanceSpecifier is_obj = result.Value();
  EXPECT_EQ(is_obj.ToString(), is_path);
}

TEST(InstanceSpecifierTest, CreateFailed1) {
  hra::core::StringView is_path("@@@RootNode/Subnode/endpoint0");
  hra::core::Result<hra::core::InstanceSpecifier> result =
      hra::core::InstanceSpecifier::Create(is_path);
  EXPECT_FALSE(result.HasValue());
  hra::core::ErrorCode error_code = result.Error();
  EXPECT_EQ(static_cast<hra::core::ErrorDomain::CodeType>(
                hra::core::CoreErrc::kInvalidMetaModelShortname),
            error_code.Value());
}

TEST(InstanceSpecifierTest, CreateFailed2) {
  hra::core::StringView is_path("@@@RootNode/Subnode/endpoint0");
  hra::core::Result<hra::core::InstanceSpecifier> result =
      hra::core::InstanceSpecifier::Create(is_path);
  EXPECT_FALSE(result.HasValue());
  hra::core::ErrorCode error_code = result.Error();
  hra::core::CoreErrorDomain *domain_ptr =
      (hra::core::CoreErrorDomain *)error_code.Domain();
  EXPECT_EQ(0x10000000, domain_ptr->Id());
  EXPECT_EQ("Core", error_code.Domain()->Name());
  EXPECT_EQ("Invalid meta model shortname",
            domain_ptr->Message(error_code.Value()));
}

TEST(InstanceSpecifierTest, CreateFailed3) {
  hra::core::StringView is_path("");
  hra::core::Result<hra::core::InstanceSpecifier> result =
      hra::core::InstanceSpecifier::Create(is_path);
  EXPECT_FALSE(result.HasValue());
  hra::core::ErrorCode error_code = result.Error();
  EXPECT_EQ(static_cast<hra::core::ErrorDomain::CodeType>(
                hra::core::CoreErrc::kInvalidMetaModelPath),
            error_code.Value());
}
