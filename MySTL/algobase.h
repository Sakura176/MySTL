#pragma once

#include <cstring>

#include "iterator.h"
#include "util.h"

namespace mystl {

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

template <class T>
const T& max(const T& lhs, const T& rhs) {
	return rhs > lhs ? rhs : lhs;
}

template <class T, class Compare>
const T& max(const T& lhs, const T& rhs, Compare comp) {
	return comp(lhs, rhs) ? rhs : lhs;
}

template <class T>
const T& min(const T& lhs, const T& rhs) {
	return rhs < lhs ? rhs : lhs;
}

template <class T, class Compare>
const T& min(const T& lhs, const T& rhs, Compare comp) {
	return comp(lhs, rhs) ? rhs : lhs;
}

/******************* copy 元素复制系列函数 ****************/

template <class InputIter, class OutputIter>
OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter result, 
							  mystl::input_iterator_tag) {
	// 循环，逐个复制元素
	DBG_OUT("copy", "input_iterator_tag");
	for (; first != last; ++first, ++result) {
		*result = *first;
	}
	return result;
}

/**
 * @brief 复制函数的随机指针版
 */
template <class RandomIter, class OutputIter>
OutputIter unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result, 
							  mystl::random_access_iterator_tag) {
	DBG_OUT("copy", "random_access_iterator_tag");
	for (auto n = last - first; n > 0; --n, ++first, ++result) {
		*result = *first;
	}
	return result;
}

template <class InputIter, class OutputIter>
OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter result) {
	return unchecked_copy_cat(first, last, result, iterator_category(first));
}

template <class Tp, class Up>
typename std::enable_if<
	std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
	std::is_trivially_copy_assignable<Up>::value, Up*>::type
unchecked_copy(Tp* first, Tp* last, Up* result) {
	const auto n = static_cast<size_t>(last - first);
	if (n != 0)
		std::memmove(result, first, n * sizeof(Up));
	return result + n;
}

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result) {
	return unchecked_copy(first, last, result);
}

/******************* copy_backward 元素移动系列函数 ****************/
// 将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内

template <class BidiIter1, class BidiIter2>
BidiIter2 unchecked_copy_backward_cat(BidiIter1 first, BidiIter1 last, BidiIter2 result, 
							  mystl::bidirectional_iterator_tag) {
	DBG_OUT("copy_backward", "bidirectional_iterator_tag");
	while (first != last) {
		*--result = *--last;
	}
	return result;
}

template <class BidiIter1, class BidiIter2>
BidiIter2 copy_backward(BidiIter1 first, BidiIter1 last, BidiIter2 result) {
	return unchecked_copy_backward_cat(first, last, result, iterator_category(result));
}

/******************* move 元素移动系列函数 ****************/
// TODO 未编写随机指针random_access_iterator_tag移动函数时，
// TODO vector默认使用input_iterator_tag函数，如何做到的？

template <class InputIter, class OutputIter>
OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter result
	, mystl::input_iterator_tag) {
	DBG_OUT("move", "input_iterator_tag");
	for (; first != last; ++first, ++result) {
		*result = mystl::move(*first);
	}
	return result;
}

template <class RandomIter, class OutputIter>
OutputIter unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result,
				mystl::random_access_iterator_tag) {
	DBG_OUT("move", "random_access_iterator_tag");
	for (int n = last - first; n > 0; --n, ++first, ++result) {
		*result = mystl::move(*first);
	}
	return result;
}

template <class InputIter, class OutputIter>
OutputIter unchecked_move(InputIter first, InputIter last, OutputIter result) {
	return unchecked_move_cat(first, last, result, iterator_category(first));
}

template <class InputIter, class OutputIter>
OutputIter move(InputIter first, InputIter last, OutputIter result) {
	return unchecked_move(first, last, result);
}

/******************* fill 填充元素系列函数 ****************/

template <class OutputIter, class Size, class T>
OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value) {
	for (; n > 0; --n, ++first) {
		*first = value;
	}
	return first;
}

template <class OutputIter, class Size, class T>
OutputIter fill_n(OutputIter first, Size n, const T& value) {
	return unchecked_fill_n(first, n, value);
}

template <class ForwardIter, class T>
void fill_cat(ForwardIter first, ForwardIter last, const T& value,
		mystl::forward_iterator_tag) {
	for (; first != last; ++first) {
		*first = value;
	}
}

template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T& value) {
	fill_cat(first, last, value, iterator_category(first));
}

}