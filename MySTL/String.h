#pragma once


#include "allocator.h"

namespace mystl {

class string {
public:
	using value_type		= char;
	using size_type			= size_t;
	using pointer			= value_type*;
	using reference			= value_type&;

	using iterator			= value_type*;
	using const_iterator 	= const value_type*;

private:
	iterator begin_;		// 起始指针
	iterator end_;			// 结束指针
	iterator cap_;			// 容量指针

	using Alloc				= Allocator<char>;

public:
	string();
	string(size_type count, value_type ch);
	string(const char* s);
	string(const char* s, size_type count);
	string(const string& oth);
	string(const string& oth, size_type pos);
	string(const string& oth, size_type pos, size_type count);
	template<class InputIt>
	string(InputIt first, InputIt last);
	string(std::initializer_list<char> ilist);

public:
	size_type size() const noexcept { return mystl::distance(begin_, end_); }
	size_type length() const noexcept { return mystl::distance(begin_, end_); }
	size_type capacity() const noexcept { return mystl::distance(begin_, cap_); }

public:
	iterator begin() { return begin_; }
	iterator end() { return end_; }

private:
	void init_space(size_type size, size_type capacity);
};

} // namespace mystl

#include "details/String.impl.h"