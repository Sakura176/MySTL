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
	//std::string exp("test string");
	//EXPECT_TRUE(isSameCon(exp, act));
}

} // namespace test
} // namespace mystl