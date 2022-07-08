/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

namespace hra {
namespace core {

// optional for object types
template <class T>
class Optional;

// In-place construction
struct in_place_t {};
constexpr in_place_t in_place{};

// Disengaged state indicator
struct nullopt_t {
  struct placeholder {};
  explicit constexpr nullopt_t(placeholder) {}
};
constexpr nullopt_t nullopt{nullopt_t::placeholder()};

namespace {  // unnamed

template <typename T>
struct is_optional : std::false_type {};
template <typename T>
struct is_optional<Optional<T>> : std::true_type {};

template <typename U, typename T>
using EnableIfConvertible =
    typename std::enable_if<std::is_convertible<U, T>::value>::type;
template <typename T>
using EnableIfCopyConstructible =
    typename std::enable_if<std::is_copy_constructible<T>::value>::type;
template <typename T>
using EnableIfMoveConstructible =
    typename std::enable_if<std::is_move_constructible<T>::value>::type;
template <typename T>
using EnableIfNotOptional = typename std::enable_if<
    !is_optional<typename std::decay<T>::type>::value>::type;
template <typename T>
using EnableIfLValueReference =
    typename std::enable_if<std::is_lvalue_reference<T>::value>::type;
template <typename T>
using EnableIfNotLValueReference =
    typename std::enable_if<!std::is_lvalue_reference<T>::value>::type;
template <typename T, typename... Args>
using EnableIfConstructible =
    typename std::enable_if<std::is_constructible<T, Args...>::value>::type;
}  // unnamed namespace

/**
 * @brief A container that contains key-value pairs with unique keys
 */
template <class T>
class Optional {
 public:
  typedef T value_type;

  /**
   * @brief Default constructor
   */
  constexpr Optional() noexcept : init(false), val(nullptr) {}
  constexpr Optional(nullopt_t) noexcept : init(false), val(nullptr) {}
  // Delete the predefined copy-constructor (for volatile, since we don't need
  // it). Doing so prevents another copy constructor from being implicitly
  // declared. This will allow us to SFINAE-in the copy-constructor when needed.
  Optional(const volatile Optional &) = delete;

  template <typename T_ = T, typename = EnableIfCopyConstructible<T_>>
  Optional(const Optional<T> &other)
      : init(other.init), val(other.init ? new T(*other.val) : nullptr) {}
  // Delete the predefined move-constructor (for volatile, since we don't need
  // it). Doing so prevents another move constructor from being implicitly
  // declared. This will allow us to SFINAE-in the move-constructor when needed.
  Optional(volatile Optional &&) = delete;

  template <typename T_ = T, typename = EnableIfMoveConstructible<T_>>
  Optional(Optional<T> &&other) noexcept(
      std::is_nothrow_move_constructible<T>::value)
      : init(other.init), val(std::move(other.val)) {}
  // Delete the predefined copy-constructor (for volatile, since we don't need
  // it). Doing so prevents another copy constructor from being implicitly
  // declared. This will allow us to SFINAE-in the copy-constructor when needed.
  Optional(const volatile T &) = delete;
  template <typename T_ = T, typename = EnableIfCopyConstructible<T_>>
  constexpr Optional(const T &v) : init(true), val(new T(v)) {}
  // Delete the predefined move-constructor (for volatile, since we don't need
  // it). Doing so prevents another move constructor from being implicitly
  // declared. This will allow us to SFINAE-in the move-constructor when needed.
  Optional(volatile T &&) = delete;
  template <typename T_ = T, typename = EnableIfMoveConstructible<T_>>
  constexpr Optional(T &&v) : init(true), val(new T(std::move(v))) {}
  template <class... Args, typename T_ = T,
            typename = EnableIfConstructible<T_, Args &&...>>
  constexpr explicit Optional(in_place_t, Args &&...args)
      : init(true), val(new T(std::forward<Args>(args)...)) {}
  template <class U, class... Args, typename T_ = T,
            typename =
                EnableIfConstructible<T_, std::initializer_list<U>, Args &&...>>
  constexpr explicit Optional(in_place_t, std::initializer_list<U> il,
                              Args &&...args)
      : init(true), val(new T(il, std::forward<Args>(args)...)) {}
  // destructor
  ~Optional() = default;

  // assignment
  Optional<T> &operator=(nullopt_t) noexcept {
    init = false;
    val.reset(nullptr);
    return *this;
  }

  Optional<T> &operator=(const Optional<T> &rhs) {
    init = rhs.init;
    val.reset(rhs.init ? new T(*rhs.val) : nullptr);
    return *this;
  }

  Optional<T> &operator=(Optional<T> &&rhs) noexcept(
      std::is_nothrow_move_assignable<T>::value
          &&std::is_nothrow_move_constructible<T>::value) {
    init = rhs.init;
    val.reset(rhs.init ? new T(std::move(*rhs.val)) : nullptr);
    return *this;
  }
  template <class U, typename = EnableIfNotOptional<U>>
  Optional<T> &operator=(U &&rhs) {
    init = true;
    val.reset(new T(std::move(rhs)));
    return *this;
  }
  template <class... Args, typename T_ = T,
            typename = EnableIfConstructible<T_, Args &&...>>
  void emplace(Args &&...args) {
    *this = nullopt;
    init = true;
    val.reset(new T(std::forward<Args>(args)...));
  }
  template <class U, class... Args, typename T_ = T,
            typename =
                EnableIfConstructible<T_, std::initializer_list<U>, Args &&...>>
  void emplace(std::initializer_list<U> il, Args &&...args) {
    *this = nullopt;
    init = true;
    val.reset(new T(il, std::forward<Args>(args)...));
  }

  void reset() noexcept {
    init = false;
    val.reset(nullptr);
  }

  // swap
  template <typename T_ = T, typename = EnableIfMoveConstructible<T_>>
  void swap(Optional<T> &rhs) noexcept(
      std::is_nothrow_move_constructible<T>::value &&noexcept(
          std::swap(std::declval<T &>(), std::declval<T &>()))) {
    std::swap(this->val, rhs.val);
    std::swap(init, rhs.init);
  }

  // observers
  constexpr T const *operator->() const { return val.get(); }
  T *operator->() { return val.get(); }
  constexpr T const &operator*() const { return *val; }
  T &operator*() { return *val; }

  constexpr bool HasValue() const noexcept { return init; }
  /*
   *  @brief Get instance possible value
   *  @returns Copied value
   *  @throws std::runtime_error Throws if there is no value
   */
  const T &Value() const & {
    if (HasValue()) {
      return *val;
    } else {
      throw std::runtime_error("Optional contains no value.");
    }
  }
  /*
   * @brief Get instance possible value
   * @returns Movable value
   * @throws std::runtime_error Throws if there is no value
   */
  T &&Value() && {
    if (HasValue()) {
      return std::move(*val);
    } else {
      throw std::runtime_error("Optional contains no value.");
    }
  }

  constexpr explicit operator bool() const noexcept { return init; }

  template <class U, typename T_ = T, typename = EnableIfCopyConstructible<T_>,
            typename = EnableIfConvertible<U &&, T_>>
  constexpr T value_or(U &&v) const & {
    return static_cast<bool>(*this) ? **this
                                    : static_cast<T>(std::forward<U>(v));
  }
  template <class U, typename T_ = T, typename = EnableIfMoveConstructible<T_>,
            typename = EnableIfConvertible<U &&, T_>>
  T value_or(U &&v) && {
    return static_cast<bool>(*this) ? std::move(**this)
                                    : static_cast<T>(std::forward<U>(v));
  }

 private:
  bool init;
  std::unique_ptr<T> val;
};

// Relational operators
template <class T>
constexpr bool operator==(const Optional<T> &x, const Optional<T> &y) {
  return static_cast<bool>(x) != static_cast<bool>(y)
             ? false
             : (!static_cast<bool>(x) ? true : *x == *y);
}
template <class T>
constexpr bool operator!=(const Optional<T> &x, const Optional<T> &y) {
  return !(x == y);
}
template <class T>
constexpr bool operator<(const Optional<T> &x, const Optional<T> &y) {
  return !static_cast<bool>(y)
             ? false
             : (!static_cast<bool>(x) ? true : std::less<T>{}(*x, *y));
}
template <class T>
constexpr bool operator>(const Optional<T> &x, const Optional<T> &y) {
  return !(x < y) && !(x == y);
}
template <class T>
constexpr bool operator<=(const Optional<T> &x, const Optional<T> &y) {
  return (x < y) || (x == y);
}
template <class T>
constexpr bool operator>=(const Optional<T> &x, const Optional<T> &y) {
  return !(x < y);
}

// Comparison with nullopt
template <class T>
constexpr bool operator==(const Optional<T> &x, nullopt_t) noexcept {
  return !static_cast<bool>(x);
}
template <class T>
constexpr bool operator==(nullopt_t, const Optional<T> &x) noexcept {
  return !static_cast<bool>(x);
}
template <class T>
constexpr bool operator!=(const Optional<T> &x, nullopt_t) noexcept {
  return !(x == nullopt);
}
template <class T>
constexpr bool operator!=(nullopt_t, const Optional<T> &x) noexcept {
  return !(nullopt == x);
}
template <class T>
constexpr bool operator<(const Optional<T> &, nullopt_t) noexcept {
  return false;
}
template <class T>
constexpr bool operator<(nullopt_t, const Optional<T> &x) noexcept {
  return static_cast<bool>(x);
}
template <class T>
constexpr bool operator<=(const Optional<T> &x, nullopt_t) noexcept {
  return (x < nullopt) || (x == nullopt);
}
template <class T>
constexpr bool operator<=(nullopt_t, const Optional<T> &x) noexcept {
  return (nullopt < x) || (nullopt == x);
}
template <class T>
constexpr bool operator>(const Optional<T> &x, nullopt_t) noexcept {
  return !(x < nullopt) && !(x == nullopt);
}
template <class T>
constexpr bool operator>(nullopt_t, const Optional<T> &x) noexcept {
  return !(nullopt < x) && !(nullopt == x);
}
template <class T>
constexpr bool operator>=(const Optional<T> &x, nullopt_t) noexcept {
  return !(x < nullopt);
}
template <class T>
constexpr bool operator>=(nullopt_t, const Optional<T> &x) noexcept {
  return !(nullopt < x);
}

// Comparison with T
template <class T>
constexpr bool operator==(const Optional<T> &x, const T &v) {
  return static_cast<bool>(x) ? *x == v : false;
}
template <class T>
constexpr bool operator==(const T &v, const Optional<T> &x) {
  return static_cast<bool>(x) ? v == *x : false;
}
template <class T>
constexpr bool operator!=(const Optional<T> &x, const T &v) {
  return !(x == v);
}
template <class T>
constexpr bool operator!=(const T &v, const Optional<T> &x) {
  return !(v == x);
}
template <class T>
constexpr bool operator<(const Optional<T> &x, const T &v) {
  return static_cast<bool>(x) ? std::less<T>{}(*x, v) : true;
}
template <class T>
constexpr bool operator<(const T &v, const Optional<T> &x) {
  return static_cast<bool>(x) ? std::less<T>{}(v, *x) : false;
}
template <class T>
constexpr bool operator<=(const Optional<T> &x, const T &v) {
  return (x < v) || (x == v);
}
template <class T>
constexpr bool operator<=(const T &v, const Optional<T> &x) {
  return (v < x) || (v == x);
}
template <class T>
constexpr bool operator>(const Optional<T> &x, const T &v) {
  return !(x < v) && !(x == v);
}
template <class T>
constexpr bool operator>(const T &v, const Optional<T> &x) {
  return !(v < x) && !(v == x);
}
template <class T>
constexpr bool operator>=(const Optional<T> &x, const T &v) {
  return !(x < v);
}
template <class T>
constexpr bool operator>=(const T &v, const Optional<T> &x) {
  return !(v < x);
}

// Specialized algorithms
template <class T>
void swap(Optional<T> &x, Optional<T> &y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}
template <class T, typename = EnableIfNotLValueReference<T>>
constexpr Optional<typename std::decay<T>::type> make_optional(T &&v) {
  return Optional<typename std::decay<T>::type>(std::forward<T>(v));
}
template <class T, typename = EnableIfLValueReference<T>>
constexpr Optional<typename std::decay<T>::type> make_optional(
    typename std::remove_reference<T>::type &&v) {
  return Optional<typename std::decay<T>::type>(
      std::forward<typename std::remove_reference<T>::type>(v));
}

// hash support
template <class T>
struct hash;
template <class T>
struct hash<Optional<T>> {
  std::size_t operator()(const Optional<T> &o) const {
    if (static_cast<bool>(o)) {
      return std::hash<T>()(*o);
    }
    return 0;
  }
};

}  // namespace core
}  // namespace hra
