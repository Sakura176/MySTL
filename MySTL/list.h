/**
 * @file list.h
 * @author your name (you@domain.com)
 * @brief STL list的实现
 * @version 0.1
 * @date 2023-10-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <assert.h>

#include "allocator.h"
#include "algobase.h"
#include "memory.h"

namespace mystl {

template <class T> struct list_node_base;
template <class T> struct list_node;

template <class T>
struct node_traits {
	using base_ptr = list_node_base<T>*;
	using node_ptr = list_node<T>*;
};


// list 节点结构
template <class T>
struct list_node_base {
	using base_ptr = typename node_traits<T>::base_ptr;
	using node_ptr = typename node_traits<T>::node_ptr;

	base_ptr prev;					// 前一节点
	base_ptr next;					// 下一节点

	list_node_base() = default;

	node_ptr as_node() {
		return static_cast<node_ptr>(self());
	}

	// 独立节点，将前节点和后节点设为自身
	void unlink() {
		prev = next = self();
	}

	// 获取节点自身指针
	base_ptr self() {
		return static_cast<base_ptr>(&*this);
	}
};

template <class T>
struct list_node : public list_node_base<T> {
	using base_ptr = typename node_traits<T>::base_ptr;
	using node_ptr = typename node_traits<T>::node_ptr;

	T value;						// 数据

	list_node() = default;
	list_node(const T& v) : value(v) {}
	list_node(T&& v) : value(mystl::move(v)) {}

	base_ptr as_base() {
		return static_cast<base_ptr>(&*this);
	}

	node_ptr self() {
		return static_cast<node_ptr>(&*this);
	}
};

// list 迭代器设计
template <class T>
struct list_iterator : public mystl::iterator<mystl::bidirectional_iterator_tag, T> {
	using value_type	 = T;
	using pointer		 = T*;
	using reference		 = T&;
	using base_ptr		 = typename node_traits<T>::base_ptr;
	using node_ptr		 = typename node_traits<T>::node_ptr;
	using self			 = list_iterator<T>;

	base_ptr node_;

	// 构造函数
	list_iterator() = default;
	list_iterator(base_ptr x) : node_(x) {}
	list_iterator(node_ptr x) : node_(x->as_base()) {}
	list_iterator(const list_iterator& rhs) : node_(rhs.node_) {}

	// 运算符重载（*、->、++、--、==、!=）
	reference operator*() const { return node_->as_node()->value; }
	pointer operator->() const { return &(operator*()); }

	self& operator++() {
		node_ = node_->next;
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--() {
		node_ = node_->prev;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const self& rhs) const { return node_ == rhs.node_; }
	bool operator!=(const self& rhs) const { return node_ != rhs.node_; }
};

template <class T>
struct list_const_iterator : public mystl::iterator<mystl::bidirectional_iterator_tag, T> {
	using value_type	 = T;
	using pointer		 = const T*;
	using reference		 = const T&;
	using base_ptr		 = typename node_traits<T>::base_ptr;
	using node_ptr		 = typename node_traits<T>::node_ptr;
	using self			 = list_const_iterator<T>;

	base_ptr node_;

	// 构造函数
	list_const_iterator() = default;
	list_const_iterator(base_ptr x) : node_(x) {}
	list_const_iterator(node_ptr x) : node_(x->as_base()) {}
	list_const_iterator(const list_iterator<T>& rhs) : node_(rhs.node_) {}

	// 运算符重载（*、->、++、--、==、!=）
	reference operator*() const { return node_->as_node()->value; }
	pointer operator->() const { return &(operator*()); }

	self& operator++() {
		node_ = node_->next;
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--() {
		node_ = node_->prev;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const self& rhs) const { return node_ == rhs.node_; }
	bool operator!=(const self& rhs) const { return node_ != rhs.node_; }
};
template <class T>
class List {
public:
	using data_alloc			= typename mystl::Allocator<T>;
	using base_alloc			= typename mystl::Allocator<list_node_base<T>>;
	using node_alloc			= typename mystl::Allocator<list_node<T>>;

	using value_type			= typename data_alloc::value_type;
	using size_type				= typename data_alloc::size_type;
	using pointer 				= typename data_alloc::pointer;
	using const_pointer			= typename data_alloc::const_pointer;
	using reference 			= typename data_alloc::reference;
	using const_reference		= typename data_alloc::const_reference;
	using difference_type		= typename data_alloc::difference_type;

	using iterator				= list_iterator<T>;
	using const_iterator 		= list_const_iterator<T>;
	using base_ptr 				= typename node_traits<T>::base_ptr;
	using node_ptr				= typename node_traits<T>::node_ptr;

private:
	base_ptr node_;
	size_type size_;

public:		// 构造、析构函数相关
	List() { fill_init(0, value_type()); };
	List(size_type count) { fill_init(count, value_type()); }
	List(size_type count, const T& value) { fill_init(count, value); }

	List(const List& other) { copy_init(other.begin(), other.end()); }
	List(List&& other) : node_(other.node_), size_(other.size_) {
		other.node_ = nullptr;
		other.size_ = 0;
	}
	List(std::initializer_list<T> init) { copy_init(init.begin(), init.end()); }

	~List() { 
		clear();
		node_alloc::deallocate(node_->as_node());
		node_ = nullptr;
		size_ = 0;
	 }

	List& operator=(const List& rhs);
	List& operator=(List&& rhs);
	List& operator=(std::initializer_list<T> ilist);

public:
	reference front() { return node_->next->as_node()->value; }
	const_reference front() const { return static_cast<const_reference>(node_->next->as_node()->value); }

	reference back() { return node_->prev->as_node()->value; }
	const_reference back() const { return static_cast<const_reference>(node_->prev->as_node()->value); }

public:		// 迭代器相关
	iterator begin() { return list_iterator<T>(node_->next); }
	const_iterator begin() const { return list_const_iterator<T>(node_->next); }

	iterator end() { return list_iterator<T>(node_); }
	const_iterator end() const { return list_const_iterator<T>(node_); }

public:
	// 容量相关
	size_type size() const { return size_; }

	bool empty() const { return size_ == 0; }

public:			// 容器修改相关
	void clear();

private:
	node_ptr create_node(const T& value);

	void fill_init(size_type count, const T& value);

	template <class Iter>
	void copy_init(Iter first, Iter last);

	void link_nodes_at_front(base_ptr first, base_ptr last);
	void link_nodes_at_back(base_ptr first, base_ptr last);
};

template <class T>
inline List<T> &List<T>::operator=(const List &rhs)
{
	clear();
	node_ = base_alloc::allocate(1);
	node_->unlink();
	size_ = rhs.size();
	try {
		for (auto cur = rhs.begin(); cur != rhs.end(); ++cur) {
			auto node = create_node(*cur);
			// 在后方插入节点
			link_nodes_at_back(node->as_base(), node->as_base());
		}
	}
	catch (...) {
		base_alloc::deallocate(node_);
		node_ = nullptr;
		throw;
	}
	return *this;
}

template <class T>
inline List<T> &List<T>::operator=(List &&rhs)
{
	node_ = rhs.node_;
	size_ = rhs.size();
	
	return *this;
}

template <class T>
inline List<T> &List<T>::operator=(std::initializer_list<T> ilist)
{
	clear();
	copy_init(ilist.begin(), ilist.end());

	return *this;
}

template <class T>
void List<T>::clear()
{
	if(node_) {
			auto cur = node_->next;
			for(base_ptr next = cur->next; cur != node_; cur = next, next = cur->next) {
				// 销毁节点
				data_alloc::destroy(mystl::address_of(cur->as_node()->value));
				node_alloc::deallocate(cur->as_node());
			}
			node_->unlink();
			size_ = 0;
		}
}

template <class T>
typename List<T>::node_ptr List<T>::create_node(const T& value) {
	node_ptr tmp = node_alloc::allocate(1);
	try {
		data_alloc::construct(mystl::address_of(tmp->value), value);
		tmp->prev = nullptr;
		tmp->next = nullptr;
	}
	catch (...) {
		node_alloc::deallocate(tmp);
		throw;
	}
	return tmp;
}

template <class T>
void List<T>::fill_init(size_type count, const T& value) {
	node_ = base_alloc::allocate(1);
	node_->unlink();
	size_ = count;
	try {
		for (; count > 0; --count) {
			auto node = create_node(value);
			// 在后方插入节点
			link_nodes_at_back(node->as_base(), node->as_base());
		}
	}
	catch (...) {
		base_alloc::deallocate(node_);
		node_ = nullptr;
		throw;
	}
}

template <class T>
template <class Iter>
void List<T>::copy_init(Iter first, Iter last) {
	node_ = base_alloc::allocate(1);
	node_->unlink();
	size_type n = mystl::distance(first, last);
	size_ = n;
	try {
		for (; n > 0; --n, ++first) {
			auto node = create_node(*first);
			link_nodes_at_back(node->as_base(), node->as_base());
		}
	}
	catch (...) {
		base_alloc::deallocate(node_);
		node_ = nullptr;
		throw;
	}
}

template <class T>
void List<T>::link_nodes_at_front(base_ptr first, base_ptr last) {
	last->prev = node_->next;
	node_->next->prev = last;
	node_->next = first;
	first->prev = node_;
}

template <class T>
void List<T>::link_nodes_at_back(base_ptr first, base_ptr last) {
	last->next = node_;
	first->prev = node_->prev;
	node_->prev->next = first;
	node_->prev = last;
}
}