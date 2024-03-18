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
	Vector();

	/**
	 * @brief 构造函数
	 * @param n 数组大小
	*/
	Vector(size_type n);

	/**
	 * @brief Construct a new Vector object
	 * 
	 * @param n 数组大小
	 * @param value 指定填充值
	 */
	Vector(size_type n, const value_type& value);

	/**
	 * @brief 拷贝构造函数
	 * 
	 * @param vec 要拷贝的Vector数组
	 */
	Vector(const Vector& vec);

	/**
	 * @brief 拷贝构造函数, 不懂该模板写法
	 * 
	 * @param begin 要拷贝数组的开始指针
	 * @param end 结束指针
	 */
	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
	Vector(Iter first, Iter last);

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
	void assign(Iter first, Iter last);
	void assign(std::initializer_list<T> ilist);

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
}

#include "details/vector.impl.h"