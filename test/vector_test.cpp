#include "../MySTL/vector.h"
#include "unittest.h"
#include <vector>

namespace mystl {
namespace test {
class VectorTest : public FUTURE_TESTBASE {
public:
    VectorTest() = default;

    void caseSetUp() override {}

    void caseTearDown() override {}
};

// 构造函数测试
TEST_F(VectorTest, vector_vector1) {
    std::vector<int> exp;
    mystl::Vector<int> act;
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_vector2) {
    std::vector<int> exp(5);
    mystl::Vector<int> act(5);
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_vector3) {
    std::vector<int> exp(6, 3);
    mystl::Vector<int> act(6, 3);
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_vector4) {
    int a[] = {1, 2, 3, 4, 5};
    std::vector<int> exp(a, a + 5);
    mystl::Vector<int> act(a, a + 5);
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_copy) {
    std::vector<int> temp_exp = {1, 2, 3, 4, 5};
    std::vector<int> exp(temp_exp);
    int a[] = {1, 2, 3, 4, 5};
    mystl::Vector<int> temp_act(a, a + 5);
    mystl::Vector<int> act(temp_act);
    EXPECT_TRUE(isSameCon(exp, act));
    std::vector<int> exp1(temp_exp.begin(), temp_exp.end());
    mystl::Vector<int> act1(temp_act.begin(), temp_act.end());
    EXPECT_TRUE(isSameCon(exp1, act1));
    std::vector<int> exp2 = temp_exp;
    mystl::Vector<int> act2 = temp_act;
    EXPECT_TRUE(isSameCon(exp2, act2));
}

TEST_F(VectorTest, vector_insert) {
    std::vector<int> exp(5, 3);
    mystl::Vector<int> act(5, 3);
    exp.insert(exp.begin() + 1, 12);
    act.insert(act.begin() + 1, 12);
    EXPECT_TRUE(isSameCon(exp, act));
    exp.insert(exp.begin() + 2, 15);
    act.insert(act.begin() + 2, 15);
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_assign) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> exp(a, a + 10);
    mystl::Vector<int> act(a, a + 10);
    exp.assign(8, 12);
    act.assign(8, 12);
    EXPECT_TRUE(isSameCon(exp, act));
    exp.assign({6, 5, 4, 3, 2, 1});
    act.assign({6, 5, 4, 3, 2, 1});
    EXPECT_TRUE(isSameCon(exp, act));
    std::vector<int> temp_exp(5, 8);
    mystl::Vector<int> temp_act(5, 8);
    exp.assign(temp_exp.begin(), temp_exp.end());
    act.assign(temp_act.begin(), temp_act.end());
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_reserve) {
    std::vector<int> exp(5, 3);
    mystl::Vector<int> act(5, 3);
    exp.reserve(17);
    act.reserve(17);
    EXPECT_TRUE(isSameCon(exp, act));
    EXPECT_EQ(exp.capacity(), act.capacity());
}

TEST_F(VectorTest, vector_clear) {
    std::vector<int> exp(5, 3);
    mystl::Vector<int> act(5, 3);
    exp.clear();
    act.clear();
    EXPECT_TRUE(isSameCon(exp, act));
}

TEST_F(VectorTest, vector_resize) {
    std::vector<int> exp(16, 3);
    mystl::Vector<int> act(16, 3);
    exp.resize(18);
    act.resize(18);
    EXPECT_TRUE(isSameCon(exp, act));
    exp.resize(7, 5);
    act.resize(7, 5);
    EXPECT_TRUE(isSameCon(exp, act));
}

} // namespace test
} // namespace mystl

