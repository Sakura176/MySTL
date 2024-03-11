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

	List& operator=(const List& rhs){
		if (this != &rhs) {
			assign(rhs.begin(), rhs.end());
		}
		return *this;
	}
	List& operator=(List&& rhs) noexcept {
		clear();
		splice(end(), rhs);
		
		return *this;
	}
	List& operator=(std::initializer_list<T> ilist);

	/**
	 * @brief 修改容器的大小和元素的值
	 * 
	 * @param count 新的大小
	 * @param value 元素的值
	 */
	void assign(size_type count, const value_type& value);
	void assign(std::initializer_list<T> ilist);
	template <class InputIt, typename std::enable_if<
	  mystl::is_input_iterator<InputIt>::value, int>::type = 0>
	void assign(InputIt first, InputIt last);

public:		// 容器操作
	void splice(const_iterator pos, List& other);
	void splice(const_iterator pos, List& other, const_iterator it);
	void splice(const_iterator pos, List& other, const_iterator first, const_iterator last);
	
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

	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);

	void push_back(const value_type& value);
	//void push_back(value_type&& value);
	void pop_back();

	void push_front(const value_type& value);
	//void push_front(value_type&& value);
	void pop_front();


	iterator insert(const_iterator pos, const value_type& value);
	iterator insert(const_iterator pos, value_type&& value);
	iterator insert(const_iterator pos, size_type count, const value_type& value);
	template <class Iter, typename std::enable_if<
	  mystl::is_input_iterator<Iter>::value, int>::type = 0 >
	iterator insert(const_iterator pos, Iter first, Iter last);

	void resize(size_type count);
	void resize(size_type count, const value_type& value);

	void swap(List& other) noexcept;

private:
	template <class ...Args>
	node_ptr create_node(Args&& ...args);

	void destroy_node(node_ptr node);

	void fill_assign(size_type n, const T& value);
	template <class Iter>
	void copy_assign(Iter first, Iter last);

	void fill_init(size_type count, const T& value);
	template <class Iter>
	void copy_init(Iter first, Iter last);

	iterator fill_insert(const_iterator pos, size_type n, const T& value);

	iterator link_iter_node(const_iterator pos, base_ptr node);

	void link_nodes_at_front(base_ptr first, base_ptr last);
	void link_nodes_at_back(base_ptr first, base_ptr last);

	/**
	 * @brief 在pos处连接节点[first, last]
	 * 
	 * @param pos 插入位置
	 * @param first 插入的起始节点
	 * @param last 插入的末尾节点
	 */
	void link_nodes(base_ptr pos, base_ptr first, base_ptr last);

	void unlink_nodes(base_ptr first, base_ptr last);
};

template <class T>
inline List<T> &List<T>::operator=(std::initializer_list<T> ilist) {
	clear();
	copy_init(ilist.begin(), ilist.end());

	return *this;
}

template <class T>
inline void List<T>::assign(size_type count, const value_type& value) {
	// TODO 待优化，在空间已申请的情况下，修改元素值是否更便捷
	fill_assign(count, value);
}

template <class T>
inline void List<T>::assign(std::initializer_list<T> ilist) {
	copy_assign(ilist.begin(), ilist.end());
}

template <class T>
template <class InputIt, typename std::enable_if<
	  mystl::is_input_iterator<InputIt>::value, int>::type>
inline void List<T>::assign(InputIt first, InputIt last) {
	copy_assign(first, last);
}

template <class T>
void List<T>::splice(const_iterator pos, List &other) {
	if (!other.empty())	{
		auto oth_f = other.node_->next;
		auto oth_l = other.node_->prev;

		other.unlink_nodes(oth_f, oth_l);
		link_nodes(pos.node_, oth_f, oth_l);

		size_ += other.size_;
		other.size_ = 0;
	}
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
List<T>::iterator List<T>::erase(const_iterator pos) {
	auto node = pos.node_;
	auto next = node->next;
	unlink_nodes(node, node);
	destroy_node(node->as_node());
	--size_;
	return iterator(next);
}

template <class T>
List<T>::iterator List<T>::erase(const_iterator first, const_iterator last) {
	if (first != last) {
		// 断开 [first, last) 间的节点
		unlink_nodes(first.node_, last.node_->prev);
		while (first != last) {
			// 释放节点
			auto node = first.node_;
			++first;
			destroy_node(node->as_node());
			--size_;
		}
	}
	return iterator(last.node_);
}

template <class T>
inline void List<T>::push_back(const value_type &value)
{
	auto node = create_node(value);
	link_nodes_at_back(node->as_base(), node->as_base());
	++size_;
}

template <class T>
inline void List<T>::pop_back()
{
	if (size() > 0)
	{
		auto end = node_->prev;
		unlink_nodes(end, end);
		destroy_node(end->as_node());
		--size_;
	}
}

template <class T>
inline void List<T>::push_front(const value_type &value)
{
	auto node = create_node(value);
	link_nodes_at_front(node->as_base(), node->as_base());
	++size_;
}

template <class T>
inline void List<T>::pop_front()
{
	if (size() > 0)
	{
		auto end = node_->next;
		unlink_nodes(end, end);
		destroy_node(end->as_node());
		--size_;
	}
}

// template <class T>
// inline void List<T>::push_back(value_type &&value)
// {
// 	push_back(mystl::move(value));
// }

template <class T>
inline typename List<T>::iterator List<T>::insert(const_iterator pos, const value_type &value)
{
	auto node = create_node(value);
	++size_;
	return link_iter_node(pos, node->as_base());
}

template <class T>
inline typename List<T>::iterator List<T>::insert(const_iterator pos, value_type&& value)
{
	auto node = create_node(value);
	++size_;
	return link_iter_node(pos, node->as_base());
}

template <class T>
inline typename List<T>::iterator 
List<T>::insert(const_iterator pos, size_type count, const value_type& value)
{
	return fill_insert(pos, count, value);
}

template <class T>
template <class Iter, typename std::enable_if<
	  mystl::is_input_iterator<Iter>::value, int>::type>
inline typename List<T>::iterator 
List<T>::insert(const_iterator pos, Iter first, Iter last) {
	iterator xpos(pos.node_);
	for(; first != last; ++first) {
		auto node = create_node(*first);
		link_nodes(xpos.node_, node->as_base(), node->as_base());
	}
	return xpos;
}

template <class T>
template <class ...Args>
typename List<T>::node_ptr List<T>::create_node(Args&& ...args) {
	node_ptr tmp = node_alloc::allocate(1);
	try {
		data_alloc::construct(mystl::address_of(tmp->value), std::forward<Args>(args)...);
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
inline void List<T>::destroy_node(node_ptr node)
{
	data_alloc::destroy(mystl::address_of(node->value));
	node_alloc::deallocate(node);
}

template <class T>
void List<T>::fill_assign(size_type n, const T& value) {
	auto i = begin();
	auto e = end();
	for (; n > 0 && i != e; --n, ++i) {
		*i = value;
	}
	if (n > 0) {
		insert(e, n, value);
	} else {
		erase(i, e);
	}
}

template <class T>
template <class Iter>
void List<T>::copy_assign(Iter first, Iter last) {
	auto i = begin();
	auto e = end();
	for (; first != last && i != e; ++first, ++i) {
		*i = *first;
	}
	if (first == last) {
		erase(i, e);
	} else {
		insert(e, first, last);
	}
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
void List<T>::copy_init(Iter first, Iter last)
{
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
inline List<T>::iterator List<T>::fill_insert(const_iterator pos, size_type n, const T &value)
{
	// 记录插入位置
	iterator xpos(pos.node_);
	if (n != 0) {
		// 记录插入节点总数
		const auto add_size = n;
		auto node = create_node(value);
		node->prev = nullptr;
		xpos = iterator(node);
		iterator end = xpos;
		try {
			for (--n; n > 0; --n, ++end) {
				auto next = create_node(value);
				end.node_->next = next->as_base();
				next->prev = end.node_;
			}
			size_ += add_size;
		} catch (...) {
			auto enode = end.node_;
			while (true) {
				auto prev = enode->prev;
				destroy_node(enode->as_node());
				if (prev == nullptr)
					break;
				enode = prev;
			}
			throw;
		}
		link_nodes(pos.node_, xpos.node_, end.node_);
	}
	return xpos;
}

template <class T>
List<T>::iterator List<T>::link_iter_node(const_iterator pos, base_ptr node) {
	if (pos == node_->next) {
		link_nodes_at_front(node, node);
	} else if (pos == node_) {
		link_nodes_at_back(node, node);
	} else {
		link_nodes(pos.node_, node, node);
	}
	return iterator(node);
}

template <class T>
void List<T>::link_nodes_at_front(base_ptr first, base_ptr last)
{
	first->prev = node_;
	last->next = node_->next;
	node_->next->prev = last;
	node_->next = first;
}

template <class T>
void List<T>::link_nodes_at_back(base_ptr first, base_ptr last) {
	last->next = node_;
	first->prev = node_->prev;
	node_->prev->next = first;
	node_->prev = last;
}

template <class T>
inline void List<T>::link_nodes(base_ptr pos, base_ptr first, base_ptr last)
{
	pos->prev->next = first;
	first->prev = pos->prev;
	pos->prev = last;
	last->next = pos;
}
template <class T>
inline void List<T>::unlink_nodes(base_ptr first, base_ptr last)
{
	first->prev->next = last->next;
	last->next->prev = first->prev;
}
}