#include <list>

#include "../MySTL/iterator.h"
#include "../MySTL/vector.h"
#include "unittest.h"

namespace mystl {
namespace test {
class IteratorTest : public FUTURE_TESTBASE {
public:
    IteratorTest() = default;
    void caseSetUp() override {}
    void caseTearDown() override {}
};

TEST_F(IteratorTest, TraitsTest) {
    mystl::Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

    auto iter = vec.begin();
	EXPECT_TRUE(mystl::has_iterator_cat<decltype(iter)>::value == false);
    // EXPECT_TRUE((std::is_same<std::random_access_iterator_tag,
    //                           typename std::iterator_traits<decltype(iter)>::iterator_category>::value));
}

}
}