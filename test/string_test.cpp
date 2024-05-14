#include <string>

#include "unittest.h"
#include "String.h"

namespace mystl {
namespace test {
class StringTest : public FUTURE_TESTBASE {
public:
    StringTest() = default;
    void caseSetUp() override {}
    void caseTearDown() override {}
};

// 构造函数测试
TEST_F(StringTest, construct1) {
	std::string exp;
	mystl::string act;
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct2) {
	std::string exp(5, 'a');
	mystl::string act(5, 'a');
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct3) {
	std::string exp("hello world!");
	mystl::string act("hello world!");
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct4) {
	std::string exp("hello world!", 5);
	mystl::string act("hello world!", 5);
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct5) {
	std::string ori1("hello world!");
	std::string exp(ori1);
	mystl::string ori2("hello world!");
	mystl::string act(ori2);
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct6) {
	std::string ori1("hello world!");
	std::string exp(ori1, 5);
	mystl::string ori2("hello world!");
	mystl::string act(ori2, 5);
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct7) {
	std::string ori1("hello world!");
	std::string exp(ori1.begin(), ori1.end());
	mystl::string ori2("hello world!");
	mystl::string act(ori2.begin(), ori2.end());
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct8) {
	std::string exp({'h', 'e', 'l', 'l', 'o'});
	mystl::string act({'h', 'e', 'l', 'l', 'o'});
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(StringTest, construct9) {
	std::string ori1("hello world!");
	std::string exp(std::move(ori1));
	mystl::string ori2("hello world!");
	mystl::string act(mystl::move(ori2));
	EXPECT_EQ(exp.size(), act.size());
	EXPECT_EQ(exp.capacity(), act.capacity());
	EXPECT_TRUE(isSameCon(exp, act));
}

} // namespace test
} // namespace mystl