/**
 * @file uninitialized.h
 * @author your name (you@domain.com)
 * @brief 用于对未初始化空间构造元素
 * @version 0.1
 * @date 2023-07-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "construct.h"
#include "iterator.h"

namespace mystl {

/*********************************** unchecked_uninit_copy **************************************/

template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, 
	ForwardIter result, std::true_type) {
	return mystl::copy(first, last, result);
}

/**
 * @brief 
 * 
 * @tparam InputIter 		输入迭代器
 * @tparam ForwardIter 		前向迭代器
 * @param first 			起始位置
 * @param last 				结束位置
 * @param result 			目标位置
 * @return ForwardIter 
 */
template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, 
	ForwardIter result, std::false_type) {
	auto cur = result;
	try {
		for (; first != last; ++first, ++cur) {
			mystl::construct(&*cur, *first);
		}
		
	}
	catch (...) {
		for (; result != cur; --cur)
			mystl::destroy(&*cur);
	}
	return cur;
}

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result) {
	return mystl::unchecked_uninit_copy(first, last, result, 
										std::is_trivially_copy_assignable<
										typename iterator_traits<ForwardIter>::
										value_type>{});
}

/**
 * @brief 赋值内容，以first为起点，复制N个至result之后
 * 
 * @tparam ForwardIter 模板迭代器类
 * @tparam Size 预算数量类
 * @tparam T 元素类型
 * @param first 需复制的迭代器起点
 * @param n 需复制元素数量
 * @param result 目标地址
 * @return ForwardIter 
 */
template <class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_copy_n(ForwardIter first, Size n, ForwardIter result, std::false_type) {
	auto cur = result;
	try {
		for (; n > 0; --n, ++cur, ++first) {
			mystl::construct(&*cur, *first);
		}
		
	}
	catch (...) {
		for (; result != cur; --cur)
			mystl::destroy(&*cur);
	}
	return cur;
}

/*********************************** unchecked_uninit_fill **************************************/

template <class ForwardIter, class Size, class T>
ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value) {
	auto cur = first;
	try {
		for (; n > 0; --n, ++cur) {
			mystl::construct(&*cur, value);
		}
	}
	catch(...)
	{
		for (; first != cur; ++first)
			mystl::destroy(&*first);
	}
	return cur;
}

template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T& value)
{
  return mystl::unchecked_uninit_fill_n(first, n, value);
}

/*********************************** uninitialized_move **************************************/
template <class InputIter, class ForwardIter>
ForwardIter unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type) {
	return mystl::move(first, last, result);
}

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result) {
	return mystl::unchecked_uninit_move(first, last, result,
										std::is_trivially_move_assignable<
										typename iterator_traits<InputIter>::
										value_type>{});
}

// template <class InputIter, class ForwardIter>
// ForwardIter unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type) {
// 	return mystl::move(first, last, result);
// }
}