/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <memory>
#include <vector>

namespace hra {
namespace core {

/**
 * @brief A sequence container that encapsulates dynamically sized arrays
 *
 * @tparam T
 * @tparam Allocator
 */
template <typename T, typename Allocator = std::allocator<T>>
using Vector = std::vector<T, Allocator>;

}  // namespace core
}  // namespace hra
