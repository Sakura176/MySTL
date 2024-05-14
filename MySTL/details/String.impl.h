#pragma once
#include "algobase.h"
#include "uninitialized.h"
#include "String.h"
namespace mystl {

#define INIT_SIZE 15

inline string::string() {
	init_space(0, size_type(INIT_SIZE));
}

string::string(size_type count, value_type ch) {
    size_type size = mystl::max(count, size_type(INIT_SIZE));
	// 1. 申请空间
	init_space(count, size);
	// 2. 填充元素
	mystl::uninitialized_fill_n(begin_, count, ch);
}

string::string(const char* s) {
	size_type size = mystl::max(strlen(s), size_type(INIT_SIZE));
	// 1. 申请空间
	init_space(strlen(s), size);

	mystl::uninitialized_copy(s, s + strlen(s), begin_);
}

inline string::string(const char *s, size_type count) {
	size_type size = mystl::max(count, size_type(INIT_SIZE));
	// 1. 申请空间
	init_space(count, size);

	mystl::uninitialized_copy(s, s + count, begin_);
}

inline string::string(const string &oth) {
	size_type size = mystl::max(oth.size(), size_type(INIT_SIZE));
	// 1. 申请空间
	init_space(oth.size(), size);

	mystl::uninitialized_copy(oth.begin_, oth.end_, begin_);
}

inline string::string(const string &oth, size_type pos) {
	size_type size = mystl::max(oth.size() - pos, size_type(INIT_SIZE));
	// 1. 申请空间
	init_space(oth.size() - pos, size);

	mystl::uninitialized_copy(oth.begin_ + pos, oth.end_, begin_);
}

inline string::string(const string &oth, size_type pos, size_type count) {
	size_type temp = mystl::min(count, size_type(oth.size() - pos));
	size_type size = mystl::max(temp, size_type(INIT_SIZE));
	// 1. 申请空间
	init_space(temp, size);

	mystl::uninitialized_copy(oth.begin_ + pos, oth.begin_ + pos + temp, begin_);
}

template<class InputIt>
inline string::string(InputIt first, InputIt last) {
	size_type temp = std::distance(first, last);
	size_type size = mystl::max(temp, size_type(INIT_SIZE));
	init_space(temp, size);
	mystl::uninitialized_copy(first, last, begin_);
}

inline string::string(std::initializer_list<char> ilist)
{
	size_type temp = std::distance(ilist.begin(), ilist.end());
	size_type size = mystl::max(temp, size_type(INIT_SIZE));
	init_space(temp, size);
	mystl::uninitialized_copy(ilist.begin(), ilist.end(), begin_);
}

inline string::string(string &&oth) noexcept
{
	this->begin_ = oth.begin_;
	this->end_ = oth.end_;
	this->cap_ = oth.cap_;
	oth.begin_ = nullptr;
	oth.end_ = nullptr;
	oth.cap_ = nullptr;
}

inline void string::assign(const string &oth)
{
	size_t size = oth.size();
	if (size < capacity())
	{
		mystl::uninitialized_copy(oth.begin(), oth.end(), begin_);
		end_ += size;
	}
}

inline string string::operator=(const string &oth)
{
	
    return string();
}

void string::init_space(size_type size, size_type capacity) {
	try	{
		begin_ = Alloc::allocate(size);
		end_ = begin_ + size;
		cap_ = begin_ + capacity;
	}
	catch(...)	{
		begin_ = nullptr;
		end_ = nullptr;
		cap_ = nullptr;
		throw;
	}
	
}

}