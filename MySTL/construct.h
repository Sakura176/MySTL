#pragma once

#include <new>

#include "type_traits.h"
#include "iterator.h"

namespace mystl {

	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @param ptr 
	 */
	template <class T>
	inline void construct(T* ptr) {
		::new(ptr) T();
	}

	/**
	 * @brief 对已存在的空间进行初始化
	 * 
	 * @tparam T1 
	 * @tparam T2 
	 * @param ptr1 指针
	 * @param value 初值
	 */
	template<class T1, class T2>
	inline void construct(T1 *ptr1, const T2& value) {
		::new(ptr1) T1(value);
	}

	template <class T>
	void destroy_one(T*, std::true_type) {}

	template <class T>
	void destroy_one(T* ptr, std::false_type) {
		if (ptr != nullptr) {
			ptr->~T();
		}
	}

	template <class T>
	void destroy(T *ptr) {
		destroy_one(ptr, std::is_trivially_destructible<T>{});
	}

	template <class ForwardIter>
	void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

	template <class ForwardIter>
	void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
		for (; first != last; ++first)
			destroy(&*first);
	}

	template <class ForwardIter>
	void destroy(ForwardIter first, ForwardIter last) {
		destroy_cat(first, last, std::is_trivially_destructible<
					typename iterator_traits<ForwardIter>::value_type>{});
	}
}