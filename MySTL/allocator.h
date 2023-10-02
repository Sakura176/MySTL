/**
 * @file allocator.h
 * @author your name (you@domain.com)
 * @brief 用于管理内存的分配、释放以及对象的构造和析构
 * @version 0.1
 * @date 2023-07-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <cstddef>

#include "construct.h"


namespace mystl {
/*
* @brief 空间适配器模板类
*/
template<class T>
class Allocator {
public:
	using size_type			= size_t;
	using value_type		= T;
	using pointer			= T *;
	using const_pointer 	= const T *;
	using reference			= T&;
	using const_reference 	= const T&;
	using difference_type	= ptrdiff_t;

public:
	/*
	* @brief 申请空间
	*/
	static T *allocate();
	/*
	* @brief 申请空间
	* @param n 空间大小
	*/
	static T *allocate(size_type n);

	/*
	* @brief 释放空间
	*/
	static void deallocate(T *ptr);
	static void deallocate(T *ptr, size_type n);

	static void construct(T* ptr);
	static void construct(T* ptr, const T& value);
	static void construct(T* ptr, T&& value);

	static void destroy(T* ptr);
	static void destroy(T* first, T* last);
};

template<class T>
T *Allocator<T>::allocate() {
	return static_cast<T *>(::operator new(sizeof(T)));
}

template<class T>
T *Allocator<T>::allocate(size_type n) {
	if (n == 0)
		return nullptr;
	return static_cast<T *>(::operator new(n * sizeof(T)));
}

template<class T>
void Allocator<T>::deallocate(T *ptr) {
	if(ptr == nullptr)
		return;
	delete ptr;
}

template<class T>
void Allocator<T>::deallocate(T *ptr, size_type n) {
	if(ptr == nullptr)
		return;
	delete ptr;
}

template <class T>
void Allocator<T>::construct(T* ptr) {
	mystl::construct(ptr);
}

template <class T>
void Allocator<T>::construct(T* ptr, const T& value) {
	mystl::construct(ptr, value);
}

template <class T>
void Allocator<T>::destroy(T* ptr) {
	mystl::destroy(ptr);
}

template <class T>
void Allocator<T>::destroy(T* first, T* last) {
	mystl::destroy(first, last);
}
}