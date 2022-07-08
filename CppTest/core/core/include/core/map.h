/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <functional>
#include <map>
#include <memory>

namespace hra {
namespace core {

/**
 * @brief A container that contains key-value pairs with unique keys.
 *
 * @tparam Key
 * @tparam T
 * @tparam Compare
 * @tparam Allocator
 */
template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<T>>
using Map = std::map<Key, T, Compare, Allocator>;

}  // namespace core
}  // namespace hra
