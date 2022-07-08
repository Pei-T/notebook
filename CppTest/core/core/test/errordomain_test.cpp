/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <gtest/gtest.h>
#include "core/error_domain.h"

enum ErrList { error1 = 1, error2, error3 };

class SampleErrorDomain : public hra::core::ErrorDomain {
 public:
  SampleErrorDomain() : ErrorDomain(0x2) {}
  explicit SampleErrorDomain(IdType domain_id) : ErrorDomain(domain_id) {}

  const char *Name() const noexcept override { return "errdomain_test"; }

  const char *Message(CodeType code_type) const noexcept override {
    if (code_type == ErrList::error1) {
      return "errdomain_test_error1";
    } else {
      return "errdomain_test_error2or3";
    }
  }
};

TEST(ErrorDomainTest, OperatorEqua) {
  SampleErrorDomain domain1;
  SampleErrorDomain domain2;
  EXPECT_TRUE(domain1 == domain2);
}

TEST(ErrorDomainTest, OperatorNotEqua) {
  SampleErrorDomain domain1(1);
  SampleErrorDomain domain2(3);
  EXPECT_TRUE(domain1 != domain2);
}

TEST(ErrorDomainTest, GetDomainId) {
  hra::core::ErrorDomain::IdType domain_id = 5;
  SampleErrorDomain domain(domain_id);
  EXPECT_EQ(domain_id, domain.Id());
}

TEST(ErrorDomainTest, GetDomainName) {
  SampleErrorDomain domain;
  EXPECT_EQ("errdomain_test", domain.Name());
}

TEST(ErrorDomainTest, GetDomainMessage) {
  SampleErrorDomain domain;
  EXPECT_EQ("errdomain_test_error1", domain.Message(ErrList::error1));
}
