/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "core/result.h"
#include <gtest/gtest.h>

enum ErrList { error1 = 1, error2, error3 };

class ResultErrorDomain : public hra::core::ErrorDomain {
 public:
  ResultErrorDomain() : ErrorDomain(0x3) {}
  explicit ResultErrorDomain(IdType domain_id) : ErrorDomain(domain_id) {}

  const char *Name() const noexcept override { return "result_test"; }

  const char *Message(CodeType code_type) const noexcept override {
    return "result_test_error";
  }
};

TEST(ResultTest, CopyValueConstructor) {
  int value = 40;
  hra::core::Result<int> result(value);

  EXPECT_TRUE(result.HasValue());
  EXPECT_EQ(value, result.Value());
}

TEST(ResultTest, MoveValueConstructor) {
  bool value = true;
  hra::core::Result<bool> result(std::move(value));

  EXPECT_TRUE(result.HasValue());
  EXPECT_EQ(value, result.Value());
  EXPECT_ANY_THROW(result.Error());
}

TEST(ResultTest, CopyErrorConstructor) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result(error_code);

  EXPECT_FALSE(result.HasValue());
  EXPECT_EQ(error_code, result.Error());
  EXPECT_TRUE(error_code == result.Error());
}

TEST(ResultTest, MoveErrorConstructor) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result(std::move(error_code));

  EXPECT_FALSE(result.HasValue());
  EXPECT_EQ(error_code.Value(), result.Error().Value());
  EXPECT_EQ(error_code, result.Error());
  EXPECT_TRUE(error_code == result.Error());
}

TEST(ResultTest, CopyConstructor) {
  hra::core::Result<int> val_result(1);
  hra::core::Result<int> copy_val_result(val_result);
  EXPECT_EQ(val_result.Value(), copy_val_result.Value());

  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> err_result(error_code);
  hra::core::Result<int> copy_err_result(err_result);
  EXPECT_EQ(err_result.Error(), copy_err_result.Error());
}

TEST(ResultTest, CopyAssign) {
  hra::core::Result<int> val_result(1);
  hra::core::Result<int> copy_val_result = val_result;
  EXPECT_EQ(val_result.Value(), copy_val_result.Value());

  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> err_result(error_code);
  hra::core::Result<int> copy_err_result = err_result;
  EXPECT_EQ(err_result.Error(), copy_err_result.Error());
}

TEST(ResultTest, MoveConstructor) {
  const int val = 1;
  hra::core::Result<int> val_result(val);
  hra::core::Result<int> move_val_result{std::move(val_result)};

  EXPECT_EQ(val, move_val_result.Value());

  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> err_result(error_code);
  hra::core::Result<int> move_err_result(std::move(err_result));

  EXPECT_EQ(err_result.Error(), move_err_result.Error());
  EXPECT_EQ(error_code.Domain()->Id(), 3);
}

TEST(ResultTest, MoveAssign) {
  hra::core::Result<int> val_result(1);
  hra::core::Result<int> move_val_result = std::move(val_result);
  EXPECT_EQ(val_result.Value(), move_val_result.Value());

  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> err_result(error_code);
  hra::core::Result<int> move_err_result = std::move(err_result);
  EXPECT_EQ(err_result.Error(), move_err_result.Error());
}

TEST(ResultTest, SwapValue) {
  const bool val1 = true;
  const bool val2 = false;
  hra::core::Result<bool> result1(val1);
  hra::core::Result<bool> result2(val2);
  result1.Swap(result2);
  EXPECT_EQ(val2, result1.Value());
  EXPECT_EQ(val1, result2.Value());
}

TEST(ResultTest, SwapError) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code1(ErrList::error1, domain);
  hra::core::ErrorCode error_code2(ErrList::error2, domain);
  hra::core::Result<int> result1(error_code1);
  hra::core::Result<int> result2(error_code2);
  result1.Swap(result2);
  EXPECT_EQ(error_code2, result1.Error());
  EXPECT_EQ(error_code1, result2.Error());
}

TEST(ResultTest, SwapMethod1) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code1(ErrList::error1, domain);
  hra::core::Result<int> result1(error_code1);

  const int val2 = 30;
  hra::core::Result<int> result2(val2);
  result1.Swap(result2);
  EXPECT_TRUE(result1.HasValue());
  EXPECT_FALSE(result2.HasValue());
}

TEST(ResultTest, SwapMethod2) {
  const int val1 = 30;
  hra::core::Result<int> result1(val1);

  ResultErrorDomain domain;
  hra::core::ErrorCode error_code2(ErrList::error2, domain);
  hra::core::Result<int> result2(error_code2);

  result1.Swap(result2);
  EXPECT_FALSE(result1.HasValue());
  EXPECT_TRUE(result2.HasValue());
}

TEST(ResultTest, SwapMethod3) {
  const bool val1 = true;
  const bool val2 = false;
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code1(ErrList::error1, domain);
  hra::core::ErrorCode error_code2(ErrList::error2, domain);

  hra::core::Result<bool> result1(val1);
  hra::core::Result<bool> result2(val2);

  result1.Swap(result2);
  EXPECT_EQ(val2, result1.Value());
  EXPECT_EQ(val1, result2.Value());

  result1.EmplaceError(std::move(error_code1));
  EXPECT_FALSE(result1.HasValue());
  result1.Swap(result2);
  EXPECT_TRUE(result1.HasValue());
  EXPECT_EQ(val1, result1.Value());
  EXPECT_FALSE(result2.HasValue());
  EXPECT_EQ(error_code1, result2.Error());

  // Revert swapping
  result1.Swap(result2);
  EXPECT_FALSE(result1.HasValue());
  EXPECT_EQ(error_code1, result1.Error());
  EXPECT_TRUE(result2.HasValue());
  EXPECT_EQ(val1, result2.Value());

  result2.EmplaceError(std::move(error_code2));
  result1.Swap(result2);
  EXPECT_EQ(error_code2, result1.Error());
  EXPECT_EQ(error_code1, result2.Error());
}

TEST(ResultTest, ValueProperty) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result(error_code);
  EXPECT_THROW(result.Value(), std::runtime_error);
}

TEST(ResultTest, ErrorProperty) {
  const bool val = 30;
  hra::core::Result<int> result(val);
  EXPECT_THROW(result.Error(), std::runtime_error);
}

TEST(ResultTest, OkMethod) {
  const int val = 30;
  hra::core::Result<int> result(val);
  // auto opt = result.Ok();
  hra::core::Optional<int> opt = result.Ok();

  EXPECT_TRUE(opt.HasValue());
}

TEST(ResultTest, ErrMethod) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result(error_code);
  auto opt = result.Err();

  EXPECT_TRUE(opt.HasValue());
}

TEST(ResultTest, ValueOrMethod) {
  const int val = 30;
  int def_val = 45;
  hra::core::Result<int> result1(val);
  EXPECT_EQ(val, result1.ValueOr(def_val));

  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result2(error_code);
  EXPECT_EQ(def_val, result2.ValueOr(def_val));
}

TEST(ResultTest, ErrorOrMethod) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result1(error_code);
  hra::core::ErrorCode def_error_code(ErrList::error3, domain);
  EXPECT_EQ(error_code, result1.ErrorOr(def_error_code));

  const int val = 1;
  hra::core::Result<int> result2(val);
  EXPECT_EQ(def_error_code, result2.ErrorOr(def_error_code));
}

TEST(ResultTest, CheckErrorMethod) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);

  const int val = 3;
  hra::core::Result<int> result(val);
  EXPECT_FALSE(result.CheckError(error_code));

  result.EmplaceError(std::move(error_code));
  EXPECT_TRUE(result.CheckError(error_code));

  const int c_err(1);
  const int c_err2(2);
  hra::core::Result<bool, int> result2(true);
  EXPECT_FALSE(result2.CheckError(c_err));
  int error(c_err);
  result2.EmplaceError(std::move(error));
  EXPECT_TRUE(result2.CheckError(c_err));
  EXPECT_FALSE(result2.CheckError(c_err2));
}

TEST(ResultTest, ResolveMethod) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result(error_code);
  auto callable = [](hra::core::ErrorCode error) { return error.Value(); };

  EXPECT_EQ(ErrList::error1, result.Resolve(callable));

  const int val = 3;
  hra::core::Result<int> result2(val);
  EXPECT_EQ(val, result2.Resolve(callable));
}

hra::core::Result<int> SomeFunction() {
  return hra::core::Result<int>::FromValue(1);
}

TEST(ResultTest, BindMethod) {
  hra::core::Result<std::string> res =
      SomeFunction()
          .Bind([](int v) { return v + 1; })
          .Bind([](int v) { return std::to_string(v); })
          .Bind([](std::string const &s) { return "'" + s + "'"; });
  EXPECT_EQ("'2'", res.Value());

  std::string t_str = "true";
  std::string f_str = "false";

  hra::core::Result<bool> result(true);
  auto callable = [t_str, f_str](bool value) { return value ? t_str : f_str; };

  hra::core::Result<std::string> res2 = result.Bind(callable);
  std::string r_str = res2.Value();
  EXPECT_EQ(t_str, r_str);
}

TEST(ResultTest, EmplaceValue) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<int> result(error_code);
  int val = 1;
  result.EmplaceValue(val);
  EXPECT_TRUE(result.HasValue());
  EXPECT_EQ(val, result.Value());
}

TEST(ResultTest, FromValue) {
  int a = 3;
  hra::core::Result<int> result =
      hra::core::Result<int>::FromValue(std::move(a));
  EXPECT_TRUE(result.HasValue());
  EXPECT_EQ(a, result.Value());
}

TEST(ResultTest, ResultCompare1) {
  hra::core::Result<std::string> result1 =
      hra::core::Result<std::string>::FromValue("abcdefg");
  hra::core::Result<std::string> result2 =
      hra::core::Result<std::string>::FromValue("hijklmn");
  EXPECT_TRUE(result1 != result2);
}

TEST(ResultTest, ResultCompare2) {
  hra::core::Result<std::string> result1 =
      hra::core::Result<std::string>::FromValue("abcdefg");
  hra::core::Result<std::string> result2 =
      hra::core::Result<std::string>::FromValue("abcdefg");
  EXPECT_TRUE(result1 == result2);
}

TEST(ResultTest, MoveAssign1) {
  hra::core::Result<std::string> result =
      hra::core::Result<std::string>::FromValue("abcdefg");
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  result = hra::core::Result<std::string>(error_code);
  EXPECT_FALSE(result.HasValue());
  EXPECT_EQ(result.Error().Value(), ErrList::error1);
}

TEST(ResultTest, MoveAssign2) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<std::string> result =
      hra::core::Result<std::string>(error_code);
  result = hra::core::Result<std::string>::FromValue("abcdefg");
  EXPECT_TRUE(result.HasValue());
  EXPECT_EQ(result.Value(), "abcdefg");
}

TEST(ResultTest, VoidConstruct) {
  hra::core::Result<void> result;
  EXPECT_TRUE(result.HasValue());
}

TEST(ResultTest, VoidCopyConstruct) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<void> result(error_code);
  hra::core::Result<void> copy_res(result);
  EXPECT_EQ(copy_res.Error(), result.Error());
}

TEST(ResultTest, VoidMoveConstruct) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<void> result(error_code);
  hra::core::Result<void> move_res(std::move(result));
  EXPECT_EQ(move_res.Error().Value(), ErrList::error1);
}

hra::core::Result<void> SomeFunction2() {
  return hra::core::Result<void>::FromValue();
}

TEST(ResultTest, GetVoidResult) {
  hra::core::Result<void> res = SomeFunction2();
  if (!res.HasValue()) {
    // if error happen, do something
  }
  EXPECT_TRUE(res.HasValue());
}

TEST(ResultTest, GetErrorResultByMistake) {
  hra::core::Result<void> result;
  EXPECT_ANY_THROW(result.Error());
}

TEST(ResultTest, VoidEmplaceError) {
  hra::core::Result<void> result;
  EXPECT_TRUE(result.HasValue());
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  result.EmplaceError(std::move(error_code));
  EXPECT_FALSE(result.HasValue());
  EXPECT_EQ(error_code, result.Error());
}

TEST(ResultTest, VoidErrorOr) {
  hra::core::Result<void> result;
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  EXPECT_EQ(error_code, result.ErrorOr(error_code));

  hra::core::ErrorCode error_code2(ErrList::error2, domain);
  result.EmplaceError(error_code2);
  EXPECT_EQ(error_code2, result.ErrorOr(error_code));
}

TEST(ResultTest, VoidCheckErrorMethod) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);

  hra::core::Result<void> result;
  EXPECT_FALSE(result.CheckError(error_code));

  result.EmplaceError(std::move(error_code));
  EXPECT_TRUE(result.CheckError(error_code));
}

TEST(ResultTest, VoidBindMethod) {
  hra::core::Result<std::string> res =
      SomeFunction2()
          .Bind([]() { return 1 + 1; })
          .Bind([](int v) { return std::to_string(v); })
          .Bind([](std::string const &s) { return "'" + s + "'"; });
  EXPECT_EQ("'2'", res.Value());
}

TEST(ResultTest, VoidMoveAssign1) {
  hra::core::Result<void> result;
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  result = hra::core::Result<void>(error_code);
  EXPECT_FALSE(result.HasValue());
  EXPECT_EQ(result.Error().Value(), ErrList::error1);
}

TEST(ResultTest, VoidMoveAssign2) {
  ResultErrorDomain domain;
  hra::core::ErrorCode error_code(ErrList::error1, domain);
  hra::core::Result<void> result = hra::core::Result<void>(error_code);
  result = hra::core::Result<void>();
  EXPECT_TRUE(result.HasValue());
}
