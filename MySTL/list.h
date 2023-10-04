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
	using base_ptr = typename list_node_base<T>*;
	using node_ptr = typename list_node<T>*;

	base_ptr prev;					// 前一节点
	base_ptr next;					// 下一节点

	list_node_base() = default;

	node_ptr as_node() {
		return static_cast<node_ptr>(self());
	}

	void unlink() {
		prev = next = self();
	}

	base_ptr self() {
		return static_cast<base_ptr>(&*this);
	}
};

template <class T>
struct list_node : public list_node_base<T> {
	using base_ptr = typename list_node_base<T>*;
	using node_ptr = typename list_node<T>*;

	T value;						// 数据

	list_node = default();
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
};

template <class T, class Alloc = Allocator<T> >
class List {

};
}