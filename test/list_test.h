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

}
}
}