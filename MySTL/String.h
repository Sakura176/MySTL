#pragma once

#include "allocator.h"
#include "iterator.h"
#include <iostream>

namespace mystl {

class string {
public:
    using value_type = char;
    using size_type = size_t;
    using pointer = value_type *;
    using reference = value_type &;

    using iterator = value_type *;
    using const_iterator = value_type const *;

private:
    iterator begin_; // 起始指针
    iterator end_;   // 结束指针
    iterator cap_;   // 容量指针

    using Alloc = Allocator<char>;

public: // 构造函数
    string();
    string(size_type count, value_type ch);
    string(char const *s);
    string(char const *s, size_type count);
    string(string const &oth);
    string(string const &oth, size_type pos);
    string(string const &oth, size_type pos, size_type count);
    template <class InputIt>
    string(InputIt first, InputIt last);
    string(std::initializer_list<char> ilist);
    string(string &&oth) noexcept;

public:
    void assign(size_type count, value_type ch);
    void assign(string const &oth);
    void assign(string const &oth, size_type pos, size_type count);
    void assign(string &&oth);
    void assign(value_type const *s, size_type count);
    void assign(value_type const *s);

public:
    string operator=(string const &oth);
    string operator=(string &&oth) noexcept;
    string operator=(char const *s);

public:
    size_type size() const noexcept {
        return mystl::distance(begin_, end_);
    }

    size_type length() const noexcept {
        return mystl::distance(begin_, end_);
    }

    size_type capacity() const noexcept {
        return mystl::distance(begin_, cap_);
    }

public:
    iterator begin() {
        return begin_;
    }

    iterator end() {
        return end_;
    }

    iterator begin() const {
        return begin_;
    }

    iterator end() const {
        return end_;
    }

private:
    void init_space(size_type size, size_type capacity);
};

} // namespace mystl

#include "details/String.impl.h"
