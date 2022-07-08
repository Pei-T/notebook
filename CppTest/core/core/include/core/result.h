/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <utility>
#include "core/error_code.h"
#include "core/optional.h"

namespace hra {
namespace core {

template <typename T, typename E = ErrorCode>
class Result final {
 public:
  // Type alias for the type T of values.
  using value_type = T;
  // Type alias for the type E of errors.
  using error_type = E;

  // Construct from the specified value(lvalue)
  Result(const T &t) : value_(t) {}
  // Construct from the specified value(rvalue)
  Result(T &&t) : value_(std::move(t)) {}

  // Construct from the specified error (lvalue).
  explicit Result(const E &e) : error_(e) {}

  // Construct from the specified error (rvalue).
  explicit Result(E &&e) : error_(std::move(e)) {}

  // Copy-construct from another instance.
  Result(const Result &other) {
    if (other.HasValue()) {
      value_ = other.value_;
    } else {
      error_ = other.error_;
    }
  }

  // Move-construct from another instance.
  Result(Result &&other) noexcept(
      std::is_nothrow_move_constructible<T>::value
          &&std::is_nothrow_move_constructible<E>::value) {
    if (other.HasValue()) {
      value_ = std::move(other.value_);
    } else {
      error_ = std::move(other.error_);
    }
  }

  ~Result() {
    value_.reset();
    error_.reset();
  }

  // Build a new Result from the specified value (lvalue)
  static Result FromValue(const T &t) { return Result(t); }
  // Build a new Result from the specified value (rvalue).
  static Result FromValue(T &&t) { return Result(std::move(t)); }

  template <typename... Args>
  static Result FromValue(Args &&...args) {
    return Result(T(std::forward<Args>(args)...));
  }

  // Build a new Result from the specified error (lvalue).
  static Result FromError(const E &e) { return Result(e); }

  // Build a new Result from the specified error (rvalue).
  static Result FromError(E &&e) { return Result(std::move(e)); }

  template <typename... Args>
  static Result FromError(Args &&...args) {
    return Result(E(std::forward<Args>(args)...));
  }

  // Copy-assign another Result to this instance.
  Result &operator=(const Result &other) {
    if (other.HasValue()) {
      value_ = other.value_;
      error_.reset();
    } else {
      error_ = other.error_;
      value_.reset();
    }
    return *this;
  }

  // Move-assign another Result to this instance.
  Result &operator=(Result &&other) noexcept(
      std::is_nothrow_move_constructible<T>::value
          &&std::is_nothrow_move_assignable<T>::value
              &&std::is_nothrow_move_constructible<E>::value
                  &&std::is_nothrow_move_assignable<E>::value) {
    if (*this != other) {
      if (other.HasValue()) {
        value_ = std::move(other.value_);
        other.value_.reset();
        error_.reset();
      } else {
        error_ = std::move(other.error_);
        other.error_.reset();
        value_.reset();
      }
    }
    return *this;
  }

  // Put a new value into this instance, constructed in-place from arguments
  template <typename... Args>
  void EmplaceValue(Args &&...args) {
    value_ = std::move(T(std::forward<Args>(args)...));
    error_.reset();
  }

  // Put a new error into this instance, constructed in-place from arguments.
  template <typename... Args>
  void EmplaceError(Args &&...args) {
    error_ = std::move(E(std::forward<Args>(args)...));
    value_.reset();
  }

  // Exchange the contents of this instance with those of other.
  void Swap(Result &other) noexcept(
      std::is_nothrow_move_constructible<T>::value
          &&std::is_nothrow_move_assignable<T>::value
              &&std::is_nothrow_move_constructible<E>::value
                  &&std::is_nothrow_move_assignable<E>::value) {
    if (HasValue() && other.HasValue()) {
      std::swap(value_, other.value_);
    } else if (HasValue() && !other.HasValue()) {
      error_ = std::move(other.error_);
      other.error_.reset();
      other.value_ = std::move(value_);
      value_.reset();
    } else if (!HasValue() && other.HasValue()) {
      value_ = std::move(other.value_);
      other.value_.reset();
      other.error_ = std::move(error_);
      error_.reset();
    } else {  // Both instances contain error
      std::swap(error_, other.error_);
    }
  }
  // Check whether *this contains a value
  bool HasValue() const noexcept { return value_.HasValue(); }
  // Check whether *this contains a value
  explicit operator bool() const noexcept { return HasValue(); }
  // Return a const_reference to the contained value
  const T &operator*() const & { return value_.Value(); }
  // Return an rvalue reference to the contained value
  T &&operator*() && { return std::move(value_).Value(); }
  // return a pointer to the contained value
  const T *operator->() const { return std::addressof(Value()); }
  // retrun a const reference to the contained value
  const T &Value() const & { return value_.Value(); }
  // Return an rvalue reference to the contained value
  T &&Value() && { return std::move(value_).Value(); }
  // Return a const reference to the contained error
  const E &Error() const & { return error_.Value(); }
  // Return an rvalue reference to the contained error
  E &&Error() && { return std::move(error_).Value(); }
  // Return the contained value as an Optional.
  Optional<T> Ok() const & { return value_; }
  Optional<T> Ok() && { return std::move(value_); }
  // Return the contained error as an Optional.
  Optional<E> Err() const & { return error_; }
  Optional<E> Err() && { return std::move(error_); }
  // Return the contained value or the given default value.
  template <typename U>
  T ValueOr(U &&defaultValue) const & {
    return value_.value_or(defaultValue);
  }
  template <typename U>
  T ValueOr(U &&defaultValue) && {
    return std::move(value_).value_or(defaultValue);
  }
  // Return the contained error or the given default error.
  template <typename G>
  E ErrorOr(G &&defaultError) const & {
    return error_.value_or(defaultError);
  }
  template <typename G>
  E ErrorOr(G &&defaultError) && {
    return std::move(error_).value_or(defaultError);
  }
  // Return whether this instance contains the given error.
  template <typename G>
  bool CheckError(G &&error) const {
    if (HasValue()) {
      // No error exists for comparison
      return false;
    } else {
      E input_error = static_cast<E>(error);
      return error_.Value() == input_error;
    }
  }

  // Return the contained value or return the result of a function call: T
  // f(const E&);
  template <typename F>
  T Resolve(F &&f) const {
    return HasValue() ? Value() : std::forward<F>(f)(Error());
  }

  template <typename F>
  auto Bind(F &&f) const -> Result<decltype(f(Value())), E> {
    using U = decltype(f(Value()));
    return HasValue() ? std::forward<F>(f)(Value()) : Result<U, E>(Error());
  }

 private:
  Optional<T> value_;
  Optional<E> error_;
};

// Specialization for void
template <typename E>
class Result<void, E> final {
 public:
  using value_type = void;
  using error_type = E;
  // Construct a new Result with a "void" value
  Result() noexcept = default;
  // Construct a new Result from the specified error
  explicit Result(const E &e) : error_(e) {}
  explicit Result(E &&e) : error_(std::move(e)) {}

  Result(const Result &other) = default;

  Result(Result &&other) noexcept(
      std::is_nothrow_move_constructible<E>::value) = default;

  ~Result() { error_.reset(); }

  static Result FromValue() noexcept { return Result(); }

  static Result FromError(const E &e) { return Result(e); }

  static Result FromError(E &&e) { return Result(std::move(e)); }

  template <typename... Args>
  static Result FromError(Args &&...args) {
    return Result(E(std::forward<Args>(args)...));
  }

  Result &operator=(const Result &other) = default;

  Result &operator=(Result &&other) noexcept(
      std::is_nothrow_move_constructible<E>::value
          &&std::is_nothrow_move_assignable<E>::value) = default;

  template <typename... Args>
  void EmplaceValue(Args &&...args) noexcept {}

  template <typename... Args>
  void EmplaceError(Args &&...args) {
    error_ = std::move(E(std::forward<Args>(args)...));
  }

  void Swap(Result &other) noexcept(
      std::is_nothrow_move_constructible<E>::value
          &&std::is_nothrow_move_assignable<E>::value) {
    if (HasError() && other.HasError()) {
      std::swap(error_, other.error_);
    } else if (HasError() && !other.HasError()) {
      other.error_ = std::move(error_);
      error_.reset();
    } else if (!HasError() && other.HasError()) {
      error_ = std::move(other.error_);
      other.error_.reset();
    }
  }
  // Check whether *this contains a value.
  bool HasValue() const noexcept { return !HasError(); }
  // Check whether *this contains a value.
  explicit operator bool() const noexcept { return HasValue(); }

  // This function only exists for helping with generic programming.
  void operator*() const {}
  // This function only exists for helping with generic programming.
  void Value() const {}
  // Access the contained error.
  const E &Error() const & { return error_.Value(); }

  E &&Error() && { return std::move(error_).Value(); }

  // Return the contained error as an Optional.
  Optional<E> Err() const & { return error_; }

  Optional<E> Err() && { return std::move(error_); }

  template <typename U>
  void ValueOr(U &&defaultValue) const {
    return HasValue() ? Value()
                      : static_cast<void>(std::forward<U>(defaultValue));
  }
  // Return the contained error or the given default error.
  template <typename G>
  E ErrorOr(G &&defaultError) const & {
    return HasError() ? Error() : static_cast<E>(std::forward<G>(defaultError));
  }

  template <typename G>
  E ErrorOr(G &&defaultError) && {
    return std::move(error_).ValueOr(defaultError);
  }
  // Return whether this instance contains the given error
  template <typename G>
  bool CheckError(G &&error) const {
    return HasValue() ? false
                      : (Error() == static_cast<E>(std::forward<G>(error)));
  }
  // Return the contained value or throw an exception.
  void ValueOrThrow() const noexcept(false) {
    throw std::runtime_error("Result<void> contains no value.");
  }
  // If *this contains a value, this function does nothing. Otherwise, the
  // specified callable is invoked.
  template <typename F>
  void Resolve(F &&f) const {
    return HasValue() ? Value() : std::forward<F>(f)(Error());
  }
  // Call the given Callable, and return a new Result with the result of the
  // call.
  template <typename F>
  auto Bind(F &&f) const -> Result<decltype(f()), E> {
    using U = decltype(f());
    if (HasError()) {
      Result<U, E> result(Error());
      return result;
    } else {
      Result<U, E> result(f());
      return result;
    }
  }

 private:
  Optional<E> error_;

  bool HasError() const noexcept { return error_.HasValue(); }
};

template <typename T, typename E>
bool operator==(Result<T, E> const &lhs, Result<T, E> const &rhs) {
  if (static_cast<bool>(lhs) != static_cast<bool>(rhs)) {
    return false;
  }
  if (lhs) {
    return lhs.Value() == rhs.Value();
  }
  return lhs.Error() == rhs.Error();
}

template <typename T, typename E>
bool operator!=(Result<T, E> const &lhs, Result<T, E> const &rhs) {
  if (static_cast<bool>(lhs) != static_cast<bool>(rhs)) {
    return true;
  }
  if (lhs) {
    return lhs.Value() != rhs.Value();
  }
  return lhs.Error() != rhs.Error();
}

}  // namespace core
}  // namespace hra
