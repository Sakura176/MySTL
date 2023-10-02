#pragma once

#include <vector>

#include "../MySTL/vector.h"
#include "test.h"

namespace mystl {
namespace test {
namespace vector_test {

// 构造函数测试
TEST(vector_vector1) {
	std::vector<int> exp;
	mystl::Vector<int> act;
	EXPECT_CON_EQ(exp, act);
}

TEST(vector_vector2) {
	std::vector<int> exp(5);
	mystl::Vector<int> act(5);
	EXPECT_CON_EQ(exp, act);
}

TEST(vector_vector3) {
	std::vector<int> exp(6, 3);
	mystl::Vector<int> act(6, 3);
	EXPECT_CON_EQ(exp, act);
}

TEST(vector_vector4) {
	int a[] = {1, 2, 3, 4, 5};
	std::vector<int> exp(a, a + 5);
	mystl::Vector<int> act(a, a + 5);
	EXPECT_CON_EQ(exp, act);
}

// TEST(vector_vector5) {
// 	std::vector<int> exp = {1, 2, 3, 4, 5};
// 	mystl::Vector<int> act = {1, 2, 3, 4, 5};
// 	EXPECT_CON_EQ(exp, act);
// }

TEST(vector_copy) {
	std::vector<int> temp_exp = {1, 2, 3, 4, 5};
	std::vector<int> exp(temp_exp);
	int a[] = {1, 2, 3, 4, 5};
	mystl::Vector<int> temp_act(a, a + 5);
	mystl::Vector<int> act(temp_act);
	EXPECT_CON_EQ(exp, act);
	std::vector<int> exp1(temp_exp.begin(), temp_exp.end());
	mystl::Vector<int> act1(temp_act.begin(), temp_act.end());
	EXPECT_CON_EQ(exp1, act1);
	std::vector<int> exp2 = temp_exp;
	mystl::Vector<int> act2 = temp_act;
	EXPECT_CON_EQ(exp2, act2);
}

TEST(vector_insert) {
	std::vector<int> exp(5, 3);
	mystl::Vector<int> act(5, 3);
	exp.insert(exp.begin() + 1, 12);
	act.insert(act.begin() + 1, 12);
	EXPECT_CON_EQ(exp, act);
	exp.insert(exp.begin() + 2, 15);
	act.insert(act.begin() + 2, 15);
	EXPECT_CON_EQ(exp, act);
}

TEST(vector_assign) {
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::vector<int> exp(a, a + 10);
	mystl::Vector<int> act(a, a + 10);
	exp.assign(8, 12);
	act.assign(8, 12);
	EXPECT_CON_EQ(exp, act);
	exp.assign({6, 5, 4, 3, 2, 1});
	act.assign({6, 5, 4, 3, 2, 1});
	EXPECT_CON_EQ(exp, act);
	std::vector<int> temp_exp(5, 8);
	mystl::Vector<int> temp_act(5, 8);
	exp.assign(temp_exp.begin(), temp_exp.end());
	act.assign(temp_act.begin(), temp_act.end());
	EXPECT_CON_EQ(exp, act);
}

TEST(vector_reserve) {
	std::vector<int> exp(5, 3);
	mystl::Vector<int> act(5, 3);
	exp.reserve(17);
	act.reserve(17);
	EXPECT_CON_EQ(exp, act);
	EXPECT_EQ(exp.capacity(), act.capacity());
}

TEST(vector_clear) {
	std::vector<int> exp(5, 3);
	mystl::Vector<int> act(5, 3);
	exp.clear();
	act.clear();
	EXPECT_CON_EQ(exp, act);
}

TEST(vector_resize) {
	std::vector<int> exp(16, 3);
	mystl::Vector<int> act(16, 3);
	exp.resize(18);
	act.resize(18);
	EXPECT_CON_EQ(exp, act);
	//EXPECT_EQ(exp.capacity(), act.capacity());
	exp.resize(7, 5);
	act.resize(7, 5);
	EXPECT_CON_EQ(exp, act);
	//EXPECT_EQ(exp.capacity(), act.capacity());
}

// void vector_test() {
// 	std::cout << "[===============================================================]" << std::endl;
// 	std::cout << "[----------------- Run container test : vector -----------------]" << std::endl;
// 	std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
// 	int a[] = {1, 2, 3, 4, 5};
// 	mystl::Vector<int> v1;
// 	COUT(v1);
// 	mystl::Vector<int> v2(5);
// 	COUT(v2);
// 	mystl::Vector<int> v3(10, 3);
// 	COUT(v3);
// 	mystl::Vector<int> v4(a, a + 5);
// 	std::vector<int> stl_v4(a, a + 3);
// 	COUT(v4);
// 	COUT(stl_v4);

// 	std::vector<int> stl_v5(10, 5);
// 	COUT(stl_v5);
// 	stl_v5.assign(v4.begin(), v4.end());
// 	COUT(stl_v5);
// 	stl_v5.assign({5, 7, 3, 8});
// 	COUT(stl_v5);
// 	stl_v5.assign(3, 12);
// 	COUT(stl_v5);
	
// 	mystl::Vector<int> v5(v2); 
// 	COUT(v5);
// 	mystl::Vector<int> v6(v5.begin(), v5.end());
// 	COUT(v6);
// 	v5 = v3;
// 	COUT(v5);
	
// 	FUN_AFTER(v1, v1.push_back(1));
// 	FUN_AFTER(v2, v2.push_back(2));
// 	FUN_AFTER(v2, v2.pop_back());
// 	FUN_AFTER(v3, v3.push_back(3));
// 	FUN_AFTER(v5, v5.push_back(5));
// 	FUN_AFTER(v6, v6.push_back(6));
// 	FUN_AFTER(v3, v3.swap(v4));
// 	FUN_AFTER(v3, v3.insert(v3.begin() + 2, 11));
// 	FUN_AFTER(v3, v3.erase(v3.begin() + 2, v3.begin() + 4));
// 	FUN_AFTER(v5, v5.assign(5, 12));
// 	FUN_AFTER(v5, v5.assign({3, 7, 5, 9}));
// 	FUN_AFTER(v5, v5.assign(v3.begin(), v3.end()));
// 	FUN_AFTER(v5, v5.erase(v5.begin() + 2));
// 	FUN_VALUE(*v2.begin());
// 	FUN_VALUE(*(v2.end() - 1));
// 	FUN_VALUE(v2.front());
// 	FUN_VALUE(v2.back());
// 	FUN_VALUE(v4[3]);
// 	FUN_VALUE(v4.at(2));
// 	PASSED;
// 	std::cout << "[----------------- End container test : vector -----------------]\n";
// }
}
}
}