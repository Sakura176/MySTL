/**
 * @file vector.h
 * @author your name (you@domain.com)
 * @brief STL Vector的实现
 * @version 0.1
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <assert.h>

#include "allocator.h"
#include "algobase.h"
#include "construct.h"
#include "uninitialized.h"
#include "exceptdef.h"
#include "iterator"
#include "memory.h"
#include "util.h"

namespace mystl {

template<class T, class Alloc = Allocator<T>>
class Vector {
public:
	using value_type		= typename Alloc::value_type;
	using size_type			= typename Alloc::size_type;
	using pointer			= typename Alloc::pointer;
	using reference			= typename Alloc::reference;
	using difference_type	= typename Alloc::difference_type;

	using iterator			= value_type*;
	using const_iterator 	= const value_type *;

private:
	iterator begin_;			// 开始元素的指针
	iterator end_;				// 尾部元素的指针
	iterator capacity_;			// 申请空间的尾部

public:
	/***************** 构造、析构相关函数 ******************/
	/**
	 * @brief 构造函数
	*/
	Vector(){ try_init(); }

	/**
	 * @brief 构造函数
	 * @param n 数组大小
	*/
	Vector(size_type n) { fill_init(n, value_type()); }

	/**
	 * @brief Construct a new Vector object
	 * 
	 * @param n 数组大小
	 * @param value 指定填充值
	 */
	Vector(size_type n, const value_type& value) { fill_init(n, value); }

	/**
	 * @brief 拷贝构造函数
	 * 
	 * @param vec 要拷贝的Vector数组
	 */
	Vector(const Vector& vec) { range_init(vec.begin_, vec.end_); }

	/**
	 * @brief 拷贝构造函数, 不懂该模板写法
	 * 
	 * @param begin 要拷贝数组的开始指针
	 * @param end 结束指针
	 */
	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
	Vector(Iter first, Iter last) { 
		MYSTL_ASSERT(!(last < first));
		range_init(first, last);
	}

	/*
	 * @brief 析构函数
	 */
	~Vector();

	/**
	 * @brief 赋值函数
	 * 
	 * @param rhs 
	 * @return Vector& 
	 */
	Vector& operator=(const Vector& rhs);
	Vector& operator=(std::initializer_list<T> ilist);

	/**
	 * @brief 赋值给容器,重新为容器内元素赋值，赋值后容器的大小和值由参数确定
	 * 
	 * @param count 新的大小
	 * @param value 新的值
	 */
	void assign(size_type count, const T& value);
	template<class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
	void assign(Iter first, Iter last) {
		copy_assign(first, last, iterator_category(first));
	}
	void assign(std::initializer_list<T> ilist) {
		copy_assign(ilist.begin(), ilist.end(), mystl::forward_iterator_tag{});
	}

public:
	/***************** 容量相关函数 ******************/
	/**
	 * @brief 获取容器内元素数量
	 * 
	 * @return size_t 元素数量
	 */
	size_t size() const {
		return static_cast<size_type>(end_ - begin_);
	}

	size_t capacity() {
		return static_cast<size_type>(capacity_ - begin_);
	}

	/**
	 * @brief 容器容量设置
	 * 
	 * @param new_cap 
	 */
	void reserve(size_type new_cap);

	/**
	 * @brief 返回容器是否为空
	 */
	bool empty() {
		return begin_ == end_;
	}

public:
	/***************** 迭代器相关函数 ******************/
	iterator begin() { return begin_; }
	const_iterator begin() const { return begin_; }

	iterator end() { return end_; }
	const_iterator end() const { return end_; }

public:
	/***************** 元素访问相关函数 ******************/
	/*
	@ brief 利用下标选取元素，运算符重载
	*/
	reference operator[](size_type pos) {
		return *(begin_ + pos);
	}

	/**
	 * @brief 选取指定位置元素
	 * 
	 * @param pos 元素索引
	 * @return reference 
	 */
	reference at(size_type pos) {
		assert(pos < size());
		return (*this)[pos];
	}

	/**
	 * @brief 获取容器内底部元素
	 * 
	 * @return reference 
	 */
	reference front() {
		assert(!empty());
		return *begin_;
	}

	/**
	 * @brief 获取容器内顶部元素
	 * 
	 * @return reference 
	 */
	reference back() {
		return *end_;
	}

	/**
	 * @brief 获取容器中数据 ?? 该函数的目的尚不明确
	 * 
	 * @return iterator 
	 */
	iterator data() {
		return *begin_;
	}

public:
	/***************** 容器修改相关函数 ******************/
	/**
	 * @brief 增加元素到容器中
	 * 
	 * @param value 元素值
	 */
	void push_back(const value_type& value);

	/**
	 * @brief TODO 容器末尾就地构造函数
	 * 
	 * @param value 
	 */
	void emplace_back(const value_type&& value);
	
	/**
	 * @brief 删除容器的顶部元素
	 * 
	 */
	void pop_back();

	/**
	 * @brief 向容器中指定位置插入元素
	 * 
	 */
	iterator insert(const_iterator pos, const T& value);
	// 指定位置插入多个元素
	iterator insert(const_iterator pos, size_type count, const T& value)
	{ return fill_insert(const_cast<iterator>(pos), count, value); }
	// TODO insert其余重载，待实现
	template <class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last);
	iterator insert(const_iterator pos, std::initializer_list<T> ilist);
	/**
	 * @brief 清除函数
	 * 
	 */
	void clear() { erase(begin(), end()); }

	/**
	 * @brief 释放指定位置函数
	 * 
	 * @param pos 
	 */
	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);

	/**
	 * @brief 指定容器大小
	 * 
	 * @param n 
	 */
	void resize(size_type n) { return resize(n, value_type()); }
	void resize(size_type n, const value_type& value);
public:
	/**
	 * @brief 
	 * 
	 * @param rhs 
	 */
	void swap(Vector& rhs);

private:
	/**
	 * @brief 申请空间并插入，用于插入时空间不足的情况
	 * 
	 * @param pos 插入位置
	 * @param value 插入元素值
	 */
	void realloc_insert(iterator pos, const value_type& value);
	iterator fill_insert(iterator pos, size_type count, const value_type& value);

	/******************** 初始化和销毁相关 ********************/
	
	/**
	 * @brief 默认初始化，申请固定大小的空间
	 * 
	*/
	void try_init() noexcept ;

	/**
	 * @brief 初始化，空间大小由用户指定
	 * 
	 * @param size 用户指定空间大小
	 * @param cap 初值空间大小，若用户指定小于初值，则使用初值大小初始化空间
	 */
	void init_space(size_type size, size_type cap);

	/**
	 * @brief 初始化且填充用户指定的内容
	 * 
	 * @param n 初始化空间大小
	 * @param value 填充的值
	 */
	void fill_init(size_type n, const value_type& value);

	/**
	 * @brief 范围初始化，根据输入的迭代器进行初始化
	 * 
	 * @tparam Iter 迭代器
	 * @param first 开始元素
	 * @param last 结束元素
	 */
	template <class Iter>
	void range_init(Iter first, Iter last);

	/**
	 * @brief 销毁已申请空间，并申请新空间
	 * 
	 * @param first 已申请空间起点
	 * @param last 已申请空间结尾
	 * @param n 新申请空间大小
	 */
	void destroy_and_recover(iterator first, iterator last, size_type n);

	/******************** 修改容器相关 ********************/
	template<class IIter>
	void copy_assign(IIter first, IIter last, input_iterator_tag);

	template<class FIter>
	void copy_assign(FIter first, FIter last, forward_iterator_tag);
};

template<class T, class Alloc>
Vector<T, Alloc>::~Vector() {
	destroy_and_recover(begin_, end_, capacity_ - begin_);
	begin_ = end_ = capacity_ = nullptr;
}

template <class T, class Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector& rhs) {
	if (this != &rhs) {
		const auto len = rhs.size();
		// 当前容器容量小于输入容器元素数量
		if (len < capacity()) {
			Vector tmp(rhs.begin(), rhs.end());
			// 交换
			swap(tmp);
		}
		// 现有容器内元素数量超过输入参数
		else if (size() >= len) {
			// 先复制输入容器的元素
			auto new_end = mystl::copy(rhs.begin(), rhs.end(), begin());
			Alloc::destroy(new_end, end_);
			end_ = begin_ + len;
		}
		else {	// 当前容器容量大于输入容器元素数量 
			// 先复制当前size数量元素
			mystl::copy(rhs.begin(), rhs.begin() + size(), begin_);
			// 剩余的申请空间并初始化
			mystl::uninitialized_copy(rhs.begin() + size(), rhs.end(), end_);
			capacity_ = end_ = begin_ + len;
		}
	}
	return *this;
}

template <class T, class Alloc>
inline Vector<T, Alloc>&
Vector<T, Alloc>::operator=(std::initializer_list<T> ilist)
{
	mystl::uninitialized_copy(ilist.begin(), ilist.end(), end_);
	capacity_ = end_ = begin_ = ilist.size();
	return *this;
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::assign(size_type count, const T &value)
{
	if (count > capacity()) {
		Vector tmp(count, value);
		swap(tmp);
	}
	else if (count > size()) {
		// 先对已有内容元素赋值
		mystl::fill(begin(), end(), value);
		// 赋值大于原有容器大小的部分
		end_ = mystl::uninitialized_fill_n(end_, count - size(), value);
	}
	else {
		auto new_end = mystl::fill_n(begin(), count, value);
		end_ = new_end;
	}
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::reserve(size_type new_cap)
{
	// 原容量小于输入参数，进行空间申请
	if (capacity() < new_cap) {
		const auto old_size = size();
		auto tmp = Alloc::allocate(new_cap);
		mystl::uninitialized_move(begin_, end_, tmp);
		begin_ = tmp;
		end_ = tmp + old_size;
		capacity_ = begin_ + new_cap;
	}
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(const value_type& value) {
	if (end_ != capacity_) {
		Alloc::construct(mystl::address_of(*end_), value);
		++end_;
	}
	else {
		realloc_insert(end_, value);
	}
}

template<class T, class Alloc>
inline void Vector<T, Alloc>::pop_back() {
	--end_;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(const_iterator pos, const T& value) {
	MYSTL_ASSERT(pos >= begin() && pos <= end());
	iterator xpos = const_cast<iterator>(pos);
	const size_type n = pos - begin_;
	if (end_ != capacity_ && xpos == end_) {
		// 容量够且插入位置在末尾
		Alloc::construct(mystl::address_of(*end_), value);
		++end_;
	}
	else if (end_ != capacity_) {
		DBG_OUT("insert", "end_ != capacity");
		// 容量够，插入位置不在末尾
		auto new_end = end_;	// 记录结尾位置
		// ？结尾前一个元素构建对象，意义不明
		Alloc::construct(mystl::address_of(*end_), *(end_ - 1));
		++new_end;
		auto value_copy = value;
		
		mystl::copy_backward(xpos, end_ - 1, end_);
		*xpos = mystl::move(value_copy);
		end_ = new_end;
	}
	else {
		realloc_insert(xpos, value);
	}
	return begin_ + n;
}

template <class T, class Alloc>
inline typename Vector<T, Alloc>::iterator 
Vector<T, Alloc>::erase(const_iterator pos) {
	MYSTL_ASSERT(pos > begin() && pos < end());

	// 移动后续元素
	iterator xpos = begin_ + (pos - begin());
	mystl::move(xpos + 1, end(), xpos);
	// 销毁多余空间
	Alloc::destroy(end_);
	--end_;
	return xpos;
}

template <class T, class Alloc>
inline typename Vector<T, Alloc>::iterator 
Vector<T, Alloc>::erase(const_iterator first, const_iterator last) {

	iterator x_begin = begin_ + (first - begin());
	iterator x_end = x_begin + (last - first);

	mystl::move(x_end, end(), x_begin);
	Alloc::destroy(end_ - (last - first), end_);
	end_ -= last - first;
	return x_begin;
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::resize(size_type n, const value_type &value)
{
	if (n < size()) {
		erase(begin() + n, end());
	}
	else {
		insert(end(), n - size(), value);
	}
}

template <class T, class Alloc>
void Vector<T, Alloc>::swap(Vector &rhs)
{
	if (this != &rhs) {
		mystl::swap(begin_, rhs.begin_);
		mystl::swap(end_, rhs.end_);
		mystl::swap(capacity_, rhs.capacity_);
	}
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::realloc_insert(iterator pos, const value_type& value) {
	// 申请双倍大小的空间
	const size_t new_size = mystl::max(capacity(), size_t(1)) * 2;	// 后续需封装成函数以应对更多的情况
	auto new_begin = Alloc::allocate(new_size);
	auto new_end = new_begin;
	const value_type& value_copy = value;

	// 移动当前元素到新空间中 
	mystl::copy(begin_, pos, new_end);

	// 插入元素
	try {
		construct(mystl::address_of(*new_end), value_copy);
		++new_end;
	}
	catch (...) {
		Alloc::deallocate(new_begin, new_size);
		throw;
	}

	// 成员变量指向新空间
	destroy_and_recover(begin_, end_, new_size);
	begin_ = new_begin;
	end_ = new_end;
	capacity_ = new_begin + new_size;

}

template <class T, class Alloc>
inline typename Vector<T, Alloc>::iterator 
Vector<T, Alloc>::fill_insert(iterator pos, size_type count, const value_type &value) {
	MYSTL_ASSERT(pos >= begin() && pos <= end());

	if (count == 0 ) return pos;

	const size_type n = pos - begin_;
	const value_type value_copy = value;
	// 容量足够插入所有元素
	if (capacity_ - end_ >= count) {
		// 插入位置后的元素数量
		const size_type after_pos = end_ - pos;
		auto old_end = end_;	// 记录结束位置

		// 移动后续位置元素
		mystl::uninitialized_move(end_ - n, end_, end_);
		end_ += count;
		mystl::uninitialized_fill_n(pos, count, value_copy);
	} 
	else {
		// 空间不够，先申请空间
		const auto new_size = count + capacity();
		auto new_begin = Alloc::allocate(new_size);
		auto new_end = new_begin;

		// 复制插入点位置前的元素
		new_end = uninitialized_move(begin_, pos, new_begin);
		new_end = uninitialized_fill_n(new_end, count, value);
		new_end = uninitialized_move(pos, end_, new_end);

		// 销毁原有空间
		Alloc::deallocate(begin_, capacity_ - begin_);
		begin_ = new_begin;
		end_ = new_end;
		capacity_ = begin_ + new_size;
	}
	return begin_ + n;
}

template <class T, class Alloc> 
inline void Vector<T, Alloc>::try_init() noexcept {
	try {
		begin_ = Alloc::allocate(16);
		end_ = begin_;
		capacity_ = begin_ + 16;
	}
	catch (...) {
		begin_ = nullptr;
		end_ = nullptr;
		capacity_ = nullptr;
	}
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::init_space(size_type size, size_type cap) {
	try {
		begin_ = Alloc::allocate(cap);
		end_ = begin_ + size;
		capacity_ = begin_ + cap;
	}
	catch (...) {
		begin_ = nullptr;
		end_ = nullptr;
		capacity_ = nullptr;
		throw;
	}
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::fill_init(size_type n, const value_type& value) {
	const size_type init_size = std::max(static_cast<size_type>(16), n);
	init_space(n, init_size);
	mystl::uninitialized_fill_n(begin_, n, value);
}

template <class T, class Alloc>
template <class Iter>
inline void Vector<T, Alloc>::range_init(Iter first, Iter last)
{
	const size_type len = mystl::distance(first, last);
	const size_type init_size = mystl::max(len, static_cast<size_type>(16));
	init_space(len, init_size);
	mystl::uninitialized_copy(first, last, begin_);
}

template <class T, class Alloc>
inline void Vector<T, Alloc>::destroy_and_recover(iterator first, iterator last, size_type n) {
	Alloc::destroy(first, last);
	Alloc::deallocate(first, n);
}

template <class T, class Alloc>
template <class IIter>
inline void Vector<T, Alloc>::copy_assign(IIter first, IIter last, input_iterator_tag) {
	// 获取容器开始迭代器
	auto cur = begin_;
	for (; first != last && cur != end_; ++cur, ++first) {
		*cur = *first;
	}
	// 容器内原先内容大于传入内容，释放原先的后续内容
	if (first == last) {
		// 释放容器内所有元素
		erase(cur + 1, end_);
		Alloc::destroy(cur + 1, end_);
		end_ = cur;
	}
	else {
		// 超出部分也需要赋值
		for (first += 1; first != last; ++first) {
			push_back(*first);
		}
	}
}

template <class T, class Alloc>
template <class FIter>
inline void Vector<T, Alloc>::copy_assign(FIter first, FIter last, forward_iterator_tag) {
	auto len = mystl::distance(first, last);
	if (len > capacity()) {
		Vector tmp(first, last);
		swap(tmp);
	}
	else if (len <= size()) {
		auto new_end = mystl::copy(first, last, begin_);
		Alloc::destroy(new_end, end_);
		end_ = new_end;
	}
	else {
		auto mid = first;
		mystl::advance(mid, size());
		mystl::copy(first, mid, begin_);
		auto new_end = uninitialized_copy(mid, last, end_);
		end_ = new_end;
	}
}
}