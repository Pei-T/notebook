/**
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>

namespace hra {
namespace core {

/**
 * @brief Array is a container that encapsulates fixed size arrays.
 *
 * @tparam value_type T
 * @tparam size_type	std::size_t
 */
template <typename T, std::size_t N>
using Array = std::array<T, N>;

}  // namespace core
}  // namespace hra
