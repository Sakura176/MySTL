#include <string>
#include <typeinfo>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class FUTURE_TESTBASE : public testing::Test {
public:
    virtual void caseSetUp() = 0;
    virtual void caseTearDown() = 0;

    void SetUp() override { caseSetUp(); }

    void TearDown() override { caseTearDown(); }

    template <class T>
    void cout_con(T& con) {
        for (auto& i : con) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    template <class T, class U>
    bool isSameCon(T& origin, U& other) {
        if (origin.size() != other.size())
        {
            std::cout << "origin.size(): " << origin.size() << std::endl;
            std::cout << "other.size(): " << other.size() << std::endl;
            return false;
        }
        for (auto i = origin.begin(), j = other.begin(); i != origin.end(); ++i, ++j) {
            if (typeid(*i) != typeid(*j))
            {
                cout_con(origin);
                cout_con(other);
                return false;
            }
        }
        return true;
    }
};

