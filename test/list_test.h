#pragma once

#include <list>

#include "../MySTL/list.h"
#include "test.h"

namespace mystl {
namespace test {
namespace list_test {

// 构造函数测试
TEST(list_list1) {
	std::list<int> exp;
	mystl::List<int> act;
	EXPECT_CON_EQ(exp, act);
}

TEST(list_list2) {
	std::list<int> exp(3);
	mystl::List<int> act(3);
	EXPECT_CON_EQ(exp, act);
}

TEST(list_list3) {
	std::list<int> exp(3, 5);
	mystl::List<int> act(3, 5);
	EXPECT_CON_EQ(exp, act);
}

TEST(list_list4) {
	std::list<int> exp(3, 5);
	std::list<int> exp1(exp);
	mystl::List<int> act(3, 5);
	mystl::List<int> act1(act);

	EXPECT_CON_EQ(exp1, act1);
}

TEST(list_list5) {
	std::list<int> exp(3, 5);
	std::list<int> exp1(std::move(exp));
	mystl::List<int> act(3, 5);
	mystl::List<int> act1(std::move(act));
	EXPECT_CON_EQ(exp1, act1);
}

TEST(list_list6) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_CON_EQ(exp, act);
}

TEST(list_iterator1) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(*(exp.begin()++), *(act.begin()++));
}


TEST(list_iterator2) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(*(--exp.end()), *(--act.end()));
}

TEST(list_operator1) {
	std::list<int> exp_temp({1, 3, 7, 9, 12});
	mystl::List<int> act_temp({1, 3, 7, 9, 12});
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp = exp_temp;
	act = act_temp;
	EXPECT_CON_EQ(exp, act);
}

TEST(list_operator2) {
	std::list<int> exp_temp({1, 3, 7, 9, 12});
	mystl::List<int> act_temp({1, 3, 7, 9, 12});
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp = std::move(exp_temp);
	act = std::move(act_temp);
	EXPECT_CON_EQ(exp, act);
}

TEST(list_operator3) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp = {1, 3, 7, 9, 12};
	act = {1, 3, 7, 9, 12};
	EXPECT_CON_EQ(exp, act);
}

TEST(list_front) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(exp.front(), act.front());
}

TEST(list_back) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(exp.back(), act.back());
}

void list_test() {
	
	mystl::List<int> act(5, 9);
	COUT(act);

	std::list<int> exp({1, 3, 5, 7});
	auto cur = exp.end();

	std::cout << *(--cur) << std::endl;

	auto act_it = act.end();

	
	FUN_VALUE(exp.front());
	FUN_VALUE(exp.back());
	FUN_VALUE(act.front());
	FUN_VALUE(act.back());
}

}
}
}