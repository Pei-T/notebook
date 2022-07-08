/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <gtest/gtest.h>
#include "core/error_code.h"

class DummyErrorDomain : public hra::core::ErrorDomain {
 public:
  DummyErrorDomain() : ErrorDomain{0x0} {}
  explicit DummyErrorDomain(IdType domain_id) : ErrorDomain{domain_id} {}

  const char *Name() const noexcept override { return "errorcode_test"; }

  const char *Message(CodeType code_type) const noexcept override {
    return "errorcode_test_error";
  }
};

TEST(ErrorCodeTest, Constructor) {
  const hra::core::ErrorDomain::CodeType raw_error_code = 1;
  DummyErrorDomain error_domain;
  hra::core::ErrorCode error_code{raw_error_code, error_domain};

  EXPECT_EQ(raw_error_code, error_code.Value());
}

TEST(ErrorCodeTest, Equality) {
  const hra::core::ErrorDomain::CodeType raw_error_code1 = 1;
  const hra::core::ErrorDomain::CodeType raw_error_code2 = 2;
  DummyErrorDomain error_domain;

  hra::core::ErrorCode error_code0{raw_error_code1, error_domain};
  hra::core::ErrorCode error_code1{raw_error_code1, error_domain};
  hra::core::ErrorCode error_code2{raw_error_code2, error_domain};

  EXPECT_TRUE(error_code0 == error_code1);
  EXPECT_TRUE(error_code0 != error_code2);
}

TEST(ErrorCodeTest, GetErrorDomain) {
  const hra::core::ErrorDomain::CodeType raw_error_code = 1;
  const hra::core::ErrorDomain::IdType domain_id = 5;
  DummyErrorDomain error_domain(domain_id);
  hra::core::ErrorCode error_code{raw_error_code, error_domain};
  DummyErrorDomain *domain_ptr = reinterpret_cast<DummyErrorDomain *>(
      const_cast<hra::core::ErrorDomain *>(error_code.Domain()));
  EXPECT_EQ(domain_id, domain_ptr->Id());
}

TEST(ErrorCodeTest, GetSupportData) {
  const hra::core::ErrorDomain::CodeType raw_error_code = 1;
  DummyErrorDomain error_domain;
  hra::core::ErrorCode error_code{raw_error_code, error_domain};
  EXPECT_EQ(0, error_code.SupportData());
}

TEST(ErrorCodeTest, GetMessage) {
  const hra::core::ErrorDomain::CodeType raw_error_code = 1;
  DummyErrorDomain error_domain;
  hra::core::ErrorCode error_code{raw_error_code, error_domain};
  EXPECT_EQ("errorcode_test_error", error_code.Message());
}
