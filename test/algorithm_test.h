#pragma once

#include <algorithm>

#include "../MySTL/vector.h"
#include "../MySTL/algobase.h"
#include "test.h"

namespace mystl {
namespace test {
namespace algorithm_test {
TEST(copy_test) {
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int exp[5], act[5];
	std::copy(arr1, arr1 + 5, exp);
	mystl::copy(arr1, arr1 + 5, act);
	EXPECT_CON_EQ(exp, act);
}

TEST(move_test) {
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {1, 2, 3, 4, 5};
	int exp[5], act[5];
	std::move(arr1, arr1 + 5, exp);
	mystl::move(arr2, arr2 + 5, act);
	EXPECT_CON_EQ(exp, act);
}

TEST(fill_test) {
	std::vector<int> exp;
	mystl::Vector<int> act;
	std::fill(exp.begin(), exp.end(), 5);
	mystl::fill(act.begin(), act.end(), 5);
	EXPECT_CON_EQ(exp, act);
}

} // namespace algorithm_test 
} // namespace test
}