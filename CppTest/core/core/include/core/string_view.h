/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace hra {
namespace core {
namespace internal {

template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string_view {
 public:
  using traits_type = Traits;
  using value_type = CharT;
  using pointer = CharT *;
  using const_pointer = CharT const *;
  using reference = CharT &;
  using const_reference = CharT const &;
  using const_iterator = CharT const *;
  using iterator = const_iterator;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using reverse_iterator = const_reverse_iterator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  constexpr static size_type npos = size_type(-1);

 public:
  // construction and assignment
  constexpr basic_string_view() noexcept : basic_string_view(nullptr, 0) {}

  constexpr basic_string_view(const_pointer p, size_type count)
      : mPtr(p), mSize(count) {}

  constexpr basic_string_view(const_pointer p)
      : basic_string_view(p, p == nullptr ? 0 : Traits::length(p)) {}

  constexpr basic_string_view(std::string const &s)
      : basic_string_view(s.c_str()) {}

  constexpr basic_string_view(basic_string_view const &other) noexcept =
      default;

  // Not "constexpr" because that would make it also "const" on C++11 compilers.
  basic_string_view &operator=(basic_string_view const &other) noexcept =
      default;

  // iterator support
  constexpr const_iterator begin() const noexcept { return mPtr; }
  constexpr const_iterator cbegin() const noexcept { return mPtr; }
  constexpr const_iterator end() const noexcept { return mPtr + mSize; }
  constexpr const_iterator cend() const noexcept { return mPtr + mSize; }
  constexpr const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  constexpr const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  constexpr const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }
  constexpr const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }

  // capacity
  constexpr size_type size() const noexcept { return mSize; }
  constexpr size_type length() const noexcept { return mSize; }
  constexpr size_type max_size() const noexcept {
    // not for wchar!
    return std::numeric_limits<size_type>::max();
  }
  constexpr bool empty() const noexcept { return mSize == 0; }

  // element access
  constexpr const_reference operator[](size_type pos) const {
    return mPtr[pos];
  }
  inline const_reference at(size_type pos) const {
    // compound statements are not allowed in C++11
    if (pos >= mSize) throw std::out_of_range("out of range");

    return mPtr[pos];
  }
  constexpr const_reference front() const { return mPtr[0]; }
  constexpr const_reference back() const { return mPtr[mSize - 1]; }
  constexpr const_pointer data() const noexcept { return mPtr; }

  // modifiers
  // Not "constexpr" because that would make it also "const" on C++11 compilers.
  void remove_prefix(size_type n) {
    mPtr += n;
    mSize -= n;
  }
  // Not "constexpr" because that would make it also "const" on C++11 compilers.
  void remove_suffix(size_type n) { mSize -= n; }
  // Not "constexpr" because that would make it also "const" on C++11 compilers.
  void swap(basic_string_view &other) noexcept {
    std::swap(mPtr, other.mPtr);
    std::swap(mSize, other.mSize);
  }

  // operations
  size_type copy(CharT *dest, size_type count, size_type pos = 0) const {
    if (pos > mSize) {
#ifndef ARA_NO_EXCEPTIONS
      throw std::out_of_range("out of range");
#else
      std::terminate();
#endif
    }
    size_t const rcount = std::min(count, mSize - pos);
    std::copy(mPtr + pos, mPtr + pos + rcount, dest);
    return rcount;
  }

  basic_string_view substr(size_type pos = 0, size_type count = npos) const {
    // compound statements are not allowed in C++11
    if (pos > mSize) {
#ifndef ARA_NO_EXCEPTIONS
      throw std::out_of_range("out of range");
#else
      std::terminate();
#endif
    }
    size_t const rcount = std::min(count, mSize - pos);
    return basic_string_view(mPtr + pos, rcount);
  }

  int compare(basic_string_view v) const noexcept {
    int ret = Traits::compare(mPtr, v.mPtr, std::min(mSize, v.mSize));

    // compound statements are not allowed in C++11
    if (ret == 0) return (mSize < v.mSize) ? -1 : (mSize > v.mSize);
    return ret;
  }

  constexpr int compare(size_type pos1, size_type count1,
                        basic_string_view v) const {
    return substr(pos1, count1).compare(v);
  }
  constexpr int compare(size_type pos1, size_type count1, basic_string_view v,
                        size_type pos2, size_type count2) const {
    return substr(pos1, count1).compare(v.substr(pos2, count2));
  }
  constexpr int compare(const_pointer s) const {
    return compare(basic_string_view(s));
  }
  constexpr int compare(size_type pos1, size_type count1,
                        const_pointer s) const {
    return substr(pos1, count1).compare(basic_string_view(s));
  }
  constexpr int compare(size_type pos1, size_type count1, const_pointer s,
                        size_type count2) const {
    return substr(pos1, count1).compare(basic_string_view(s, count2));
  }

  size_type find(basic_string_view v, size_type pos = 0) const noexcept {
    return find(v.data(), pos, v.size());
  }
  size_type find(CharT ch, size_type pos = 0) const noexcept {
    return std::basic_string<CharT, Traits>(mPtr, mSize).find(ch, pos);
  }
  size_type find(const_pointer s, size_type pos, size_type count) const {
    return std::basic_string<CharT, Traits>(mPtr, mSize).find(s, pos, count);
  }
  size_type find(const_pointer s, size_type pos = 0) const {
    return find(s, pos, Traits::length(s));
  }

  size_type rfind(basic_string_view v, size_type pos = npos) const noexcept {
    return rfind(v.data(), pos, v.size());
  }
  size_type rfind(CharT c, size_type pos = npos) const noexcept {
    return std::basic_string<CharT, Traits>(mPtr, mSize).rfind(c, pos);
  }
  size_type rfind(const_pointer s, size_type pos, size_type count) const {
    return std::basic_string<CharT, Traits>(mPtr, mSize).rfind(s, pos, count);
  }
  size_type rfind(const_pointer s, size_type pos = npos) const {
    return rfind(s, pos, Traits::length(s));
  }

  size_type find_first_of(basic_string_view v,
                          size_type pos = 0) const noexcept {
    return find_first_of(v.data(), pos, v.size());
  }
  size_type find_first_of(CharT c, size_type pos = 0) const noexcept {
    return std::basic_string<CharT, Traits>(mPtr, mSize).find_first_of(c, pos);
  }
  size_type find_first_of(const_pointer s, size_type pos,
                          size_type count) const {
    return std::basic_string<CharT, Traits>(mPtr, mSize)
        .find_first_of(s, pos, count);
  }
  size_type find_first_of(const_pointer s, size_type pos = 0) const {
    return find_first_of(s, pos, Traits::length(s));
  }

  size_type find_last_of(basic_string_view v,
                         size_type pos = npos) const noexcept {
    return find_last_of(v.data(), pos, v.size());
  }
  size_type find_last_of(CharT c, size_type pos = npos) const noexcept {
    return std::basic_string<CharT, Traits>(mPtr, mSize).find_last_of(c, pos);
  }
  size_type find_last_of(const_pointer s, size_type pos, size_type cnt) const {
    return std::basic_string<CharT, Traits>(mPtr, mSize)
        .find_last_of(s, pos, cnt);
  }
  size_type find_last_of(const_pointer s, size_type pos = npos) const {
    return find_last_of(s, pos, Traits::length(s));
  }

  size_type find_first_not_of(basic_string_view v,
                              size_type pos = 0) const noexcept {
    return find_first_not_of(v.data(), pos, v.size());
  }
  size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept {
    return std::basic_string<CharT, Traits>(mPtr, mSize)
        .find_first_not_of(c, pos);
  }
  size_type find_first_not_of(const_pointer s, size_type pos,
                              size_type count) const {
    return std::basic_string<CharT, Traits>(mPtr, mSize)
        .find_first_not_of(s, pos, count);
  }
  size_type find_first_not_of(const_pointer s, size_type pos = 0) const {
    return find_first_not_of(s, pos, Traits::length(s));
  }

  size_type find_last_not_of(basic_string_view v,
                             size_type pos = npos) const noexcept {
    return find_last_not_of(v.data(), pos, v.size());
  }
  size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept {
    return std::basic_string<CharT, Traits>(mPtr, mSize)
        .find_last_not_of(c, pos);
  }
  size_type find_last_not_of(const_pointer s, size_type pos,
                             size_type count) const {
    return std::basic_string<CharT, Traits>(mPtr, mSize)
        .find_last_not_of(s, pos, count);
  }
  size_type find_last_not_of(const_pointer s, size_type pos = npos) const {
    return find_last_not_of(s, pos, Traits::length(s));
  }

 private:
  CharT const *mPtr;
  size_type mSize;
};

// inserters and extractors
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits> &operator<<(
    std::basic_ostream<CharT, Traits> &os,
    basic_string_view<CharT, Traits> const &v) {
  os << std::basic_string<CharT, Traits>(v.data(), v.size());
  return os;
}

// non-member comparison functions,
//         incl. additional overloads

// Helper type for forcing template argument deduction to proceed based on
// only one of the arguments to a comparison operator. See n3766 for details.
template <typename T>
using Identity = typename std::decay<T>::type;

template <typename CharT, typename Traits>
constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) == 0;
}
template <typename CharT, typename Traits>
constexpr bool operator==(
    basic_string_view<CharT, Traits> lhs,
    Identity<basic_string_view<CharT, Traits>> rhs) noexcept {
  return lhs.compare(rhs) == 0;
}
template <typename CharT, typename Traits>
constexpr bool operator==(Identity<basic_string_view<CharT, Traits>> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits>
constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) != 0;
}
template <typename CharT, typename Traits>
constexpr bool operator!=(
    basic_string_view<CharT, Traits> lhs,
    Identity<basic_string_view<CharT, Traits>> rhs) noexcept {
  return lhs.compare(rhs) != 0;
}
template <typename CharT, typename Traits>
constexpr bool operator!=(Identity<basic_string_view<CharT, Traits>> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) != 0;
}

template <typename CharT, typename Traits>
constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                         basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) < 0;
}
template <typename CharT, typename Traits>
constexpr bool operator<(
    basic_string_view<CharT, Traits> lhs,
    Identity<basic_string_view<CharT, Traits>> rhs) noexcept {
  return lhs.compare(rhs) < 0;
}
template <typename CharT, typename Traits>
constexpr bool operator<(Identity<basic_string_view<CharT, Traits>> lhs,
                         basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits>
constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                         basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) > 0;
}
template <typename CharT, typename Traits>
constexpr bool operator>(
    basic_string_view<CharT, Traits> lhs,
    Identity<basic_string_view<CharT, Traits>> rhs) noexcept {
  return lhs.compare(rhs) > 0;
}
template <typename CharT, typename Traits>
constexpr bool operator>(Identity<basic_string_view<CharT, Traits>> lhs,
                         basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits>
constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) <= 0;
}
template <typename CharT, typename Traits>
constexpr bool operator<=(
    basic_string_view<CharT, Traits> lhs,
    Identity<basic_string_view<CharT, Traits>> rhs) noexcept {
  return lhs.compare(rhs) <= 0;
}
template <typename CharT, typename Traits>
constexpr bool operator<=(Identity<basic_string_view<CharT, Traits>> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits>
constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) >= 0;
}
template <typename CharT, typename Traits>
constexpr bool operator>=(
    basic_string_view<CharT, Traits> lhs,
    Identity<basic_string_view<CharT, Traits>> rhs) noexcept {
  return lhs.compare(rhs) >= 0;
}
template <typename CharT, typename Traits>
constexpr bool operator>=(Identity<basic_string_view<CharT, Traits>> lhs,
                          basic_string_view<CharT, Traits> rhs) noexcept {
  return lhs.compare(rhs) >= 0;
}

}  // namespace internal

// @brief A read-only view over a contiguous sequence of characters, the storage
// of which is owned by another object.
using StringView = internal::basic_string_view<char>;

}  // namespace core
}  // namespace hra
