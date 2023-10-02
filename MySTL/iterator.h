#pragma once

#include <cstddef>

#include "type_traits.h"

namespace mystl {

// 五种迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/**
 * @brief 迭代器模板
 * 
 * @tparam Category 	迭代器的类型
 * @tparam T 			数据类型
 * @tparam Distance 	迭代器距离类型
 * @tparam Pointer 		容器中元素的指针类型
 * @tparam Reference 	容器中元素的引用类型
 */
template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
struct iterator {
	using iterator_category		= Category;
	using value_type			= T;
	using pointer				= Pointer;
	using reference				= Reference;
	using difference_type		= Distance;
};

// iterator traits
/**
 * @brief 判断是否含有迭代器类型
 * 
 * @tparam T 迭代器类
 */
template <class T>
struct has_iterator_cat {
private:
	struct two { char a; char b; };
	// 利用模板特性确定调用的函数，从而设置value的值
	template <class U> static two test(...);
	template <class U> static char test(typename U::iterator_category* = 0);
public:
	// 静态成员函数，该值根据传入数据是否包含iterator_category类型确定
	static const bool value = sizeof(test<T>(0)) == sizeof(char);
};


template <class Iterator, bool>
struct iterator_traits_impl {};

// 偏特化，类型为true时，则构建迭代器萃取类
template <class Iterator>
struct iterator_traits_impl<Iterator, true> {
	using iterator_category		= typename Iterator::iterator_category;
	using value_type			= typename Iterator::value_type;
	using pointer				= typename Iterator::pointer;
	using reference				= typename Iterator::reference;
	using difference_type		= typename Iterator::difference_type;
};

template <class Iterator, bool>
struct iterator_traits_helper {};

// 进一步判断迭代器能否隐式转换为输入或输出迭代器
template <class Iterator>
struct iterator_traits_helper<Iterator, true> : public iterator_traits_impl<Iterator,
	std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
	std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
{  };

// 萃取迭代器的特性
template <class Iterator>
struct iterator_traits 
	: public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

// 针对原生指针 T* 的偏特化版本
template <class T>
struct iterator_traits<T*> {
	using iterator_category		= random_access_iterator_tag;
	using value_type 			= T;
	using pointer 				= T*;
	using reference 			= T&;
	using difference_type 		= ptrdiff_t;
};

// 针对原生指针 cosnt T* 的偏特化版本
template <class T>
struct iterator_traits<const T*> {
	using iterator_category		= random_access_iterator_tag;
	using value_type 			= T;
	using pointer 				= const T*;
	using reference 			= const T&;
	using difference_type 		= ptrdiff_t;
};

template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of : public m_bool_constant<std::is_convertible<
	typename iterator_traits<T>::iterator_category, U>::value>
{
};

// 萃取某种迭代器
template <class T, class U>
struct has_iterator_cat_of<T, U, false> : public m_false_type {};

template <class Iter>
struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

template <class Iter>
struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

template <class Iter>
struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

template <class Iter>
struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

template <class Iter>
struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

template <class Iterator>
struct is_iterator :
	public m_bool_constant<is_input_iterator<Iterator>::value ||
		is_output_iterator<Iterator>::value>
{
};

// 萃取某个迭代器的 category
template <class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
	typedef typename iterator_traits<Iterator>::iterator_category Category;
	return Category();
}

// 萃取某个迭代器的 value_type
template <class Iterator>
typename iterator_traits<Iterator>::value_type* 
value_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// 萃取某个迭代器的 distance_type
template <class Iterator>
typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 以下函数用于计算迭代器间的距离

// distance 的 input_iterator_tag 的版本
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag) {
	typename iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

template <class RandomIter>
typename iterator_traits<RandomIter>::difference_type 
distance_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag) {
	return last - first;
}

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type 
distance(InputIterator first, InputIterator last) {
	return distance_dispatch(first, last, iterator_category(first));
}

/************************** 迭代器移动 ************************/
template <class InputIterator, class Distance>
void advance_dispatch(InputIterator& first, Distance n, input_iterator_tag) {
	while(n--) {
		++first;
	}
}

template <class InputIterator, class Distance>
void advance(InputIterator& first, Distance n) {
	advance_dispatch(first, n, iterator_category(first));
}
} // namespace mystl