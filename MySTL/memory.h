/**
 * @file memory.h
 * @author your name (you@domain.com)
 * @brief 动态内存管理头文件
 * @version 0.1
 * @date 2023-08-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstddef>
#include <cstdlib>
#include <climits>

namespace mystl {
/**
 * @brief 获取对象地址
 * 
 * @tparam T 
 * @param value 
 * @return constexpr T* 
 */
template <class T>
constexpr T* address_of(T& value) noexcept {
	return &value;
}

}