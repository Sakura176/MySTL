#include <list>

#include "../MySTL/list.h"
#include "unittest.h"

namespace mystl {
namespace test {
class ListTest : public FUTURE_TESTBASE {
public:
    ListTest() = default;
    void caseSetUp() override {}
    void caseTearDown() override {}
};

// 构造函数测试
TEST_F(ListTest, list_list1) {
	std::list<int> exp;
	mystl::List<int> act;
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_list2) {
	std::list<int> exp(3);
	mystl::List<int> act(3);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_list3) {
	std::list<int> exp(3, 5);
	mystl::List<int> act(3, 5);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_list4) {
	std::list<int> exp(3, 5);
	std::list<int> exp1(exp);
	mystl::List<int> act(3, 5);
	mystl::List<int> act1(act);

	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_list5) {
	std::list<int> exp(3, 5);
	std::list<int> exp1(std::move(exp));
	mystl::List<int> act(3, 5);
	mystl::List<int> act1(std::move(act));
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_list6) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_iterator1) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(*(exp.begin()++), *(act.begin()++));
}


TEST_F(ListTest, list_iterator2) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(*(--exp.end()), *(--act.end()));
}

TEST_F(ListTest, list_operator1) {
	std::list<int> exp_temp({1, 3, 7, 9, 12});
	mystl::List<int> act_temp({1, 3, 7, 9, 12});
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp = exp_temp;
	act = act_temp;
	EXPECT_TRUE(isSameCon(exp, act));
}

// TEST_F(ListTest, list_operator2) {
// 	std::list<int> exp_temp({1, 3, 7, 9, 12});
// 	mystl::List<int> act_temp({1, 3, 7, 9, 12});
// 	std::list<int> exp({3, 7, 9});
// 	mystl::List<int> act({3, 7, 9});
// 	exp = std::move(exp_temp);
// 	act = mystl::move(act_temp);
// 	EXPECT_TRUE(isSameCon(exp, act));
// }

TEST_F(ListTest, list_operator3) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp = {1, 3, 7, 9, 12};
	act = {1, 3, 7, 9, 12};
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_assign1) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.assign(5, 11);
	act.assign(5, 11);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_assign2) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp.assign({1, 3, 7, 9, 12});
	act.assign({1, 3, 7, 9, 12});
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_splice1) {
	std::list<int> exp_tmp({10, 20, 30});
	mystl::List<int> act_tmp({10, 20, 30});
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	exp.splice(exp.begin()++, exp_tmp);
	act.splice(act.begin()++, act_tmp);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_insert1) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.insert(++exp.begin(), 12);
	act.insert(++act.begin(), 12);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_insert2) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.insert(++exp.begin(), 3, 12);
	act.insert(++act.begin(), 3, 12);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_push_back) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.push_back(5);
	act.push_back(5);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_push_front) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.push_front(5);
	act.push_front(5);
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_pop_back) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.pop_back();
	act.pop_back();
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_pop_front) {
	std::list<int> exp({1, 3, 9});
	mystl::List<int> act({1, 3, 9});
	exp.pop_front();
	act.pop_front();
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(ListTest, list_front) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(exp.front(), act.front());
}

TEST_F(ListTest, list_back) {
	std::list<int> exp({3, 7, 9});
	mystl::List<int> act({3, 7, 9});
	EXPECT_EQ(exp.back(), act.back());
}

// void list_test() {
	
// 	mystl::List<int> act(5, 9);
// 	COUT(act);

// 	std::list<int> exp({1, 3, 5, 7});
// 	auto cur = exp.end();

// 	FUN_VALUE(exp.front());
// 	FUN_VALUE(exp.back());
// 	FUN_VALUE(act.front());
// 	FUN_VALUE(act.back());
// }

}
}