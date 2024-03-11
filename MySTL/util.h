#pragma once

#include <cstddef>
#include <stdio.h>

#include "type_traits.h"

namespace mystl {

#ifdef DEBUG
#define DBG_OUT(str, info) printf("[%s]: %s\n", str, info)
#endif

// move 移动指针
template <typename T>
constexpr typename std::remove_reference<T>::type&& move(T&& arg) {
	return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

/****************** swap ****************/

template <class Tp>
void swap(Tp& lhs, Tp&rhs) {
	auto tmp(mystl::move(lhs));
	lhs = mystl::move(rhs);
	rhs = mystl::move(tmp);
}
}