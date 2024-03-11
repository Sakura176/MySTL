#include <algorithm>
#include <gtest/gtest.h>
#include "unittest.h"

#include "../MySTL/vector.h"
#include "../MySTL/algobase.h"

namespace mystl {
namespace test {
class AlgorithmTest : public FUTURE_TESTBASE {
public:
    AlgorithmTest() = default;
    void caseSetUp() override {}
    void caseTearDown() override {}

	bool isSameArr(int* a, int* b) {
		while (*a == *b) {
			++a;
			++b;
		}
		return *a > *b;
	}
};

TEST_F(AlgorithmTest, copy_test) {
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int exp[5], act[5];
	std::copy(arr1, arr1 + 5, exp);
	mystl::copy(arr1, arr1 + 5, act);
	EXPECT_TRUE(isSameArr(exp, act));
}

TEST_F(AlgorithmTest, move_test) {
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {1, 2, 3, 4, 5};
	int exp[5], act[5];
	std::move(arr1, arr1 + 5, exp);
	mystl::move(arr2, arr2 + 5, act);
	EXPECT_TRUE(isSameArr(exp, act));
}

TEST_F(AlgorithmTest, fill_test) {
	std::vector<int> exp;
	mystl::Vector<int> act;
	std::fill(exp.begin(), exp.end(), 5);
	mystl::fill(act.begin(), act.end(), 5);
	EXPECT_TRUE(isSameCon(exp, act));
}

} // namespace test 
} // namespace mystl