#include <algorithm>
#include <gtest/gtest.h>
#include "unittest.h"

#include "../MySTL/vector.h"
#include "../MySTL/algobase.h"

namespace mystl {
namespace test {

#define LEN(a) sizeof(a) / sizeof(a[0])

class AlgorithmTest : public FUTURE_TESTBASE {
public:
    AlgorithmTest() = default;
    void caseSetUp() override {}
    void caseTearDown() override {}

	bool isSameArr(int a[], int b[], int len_a, int len_b) {
		if (len_a != len_b) return false;
		for (int i = 0; i < len_a; ++i) {
			if (a[i] != b[i]) return false;
		}

		return true;
	}
};

TEST_F(AlgorithmTest, copy_test) {
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int exp[5], act[5];
	std::copy(arr1, arr1 + 5, exp);
	mystl::copy(arr1, arr1 + 5, act);
	EXPECT_TRUE(isSameArr(exp, act, LEN(exp), LEN(act)));
}

TEST_F(AlgorithmTest, move_test) {
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {1, 2, 3, 4, 5};
	int exp[5], act[5];
	std::move(arr1, arr1 + 5, exp);
	mystl::move(arr2, arr2 + 5, act);
	EXPECT_TRUE(isSameArr(exp, act, LEN(exp), LEN(act)));
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