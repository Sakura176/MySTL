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
	iterator _begin;		// 起始指针
	iterator _end;			// 结束指针
	iterator _cap;			// 容量指针

	using Alloc				= Allocator<char>;

public:
	string() : _begin(0), _end(0), _cap(0) {};
	string(size_type count, value_type ch);
	string(const string& oth, size_type pos);
	string(const string& oth, size_type pos, size_type count);
	string(const char* s);
	string(const char* s, size_type count);
	template<class InputIt>
	string(InputIt first, InputIt last);

public:
	size_type size() const noexcept { return mystl::distance(_begin, _end); }
	size_type length() const noexcept { return mystl::distance(_begin, _end); }
	size_type capacity() const noexcept { return mystl::distance(_begin, _end); }
};

} // namespace mystl

#include "details/vector.impl.h"