/**
 * @file test.h
 * @author your name (you@domain.com)
 * @brief 简易单元测试框架
 * @version 0.1
 * @date 2023-07-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "Lib/redbud/io/color.h"

namespace mystl {

namespace test {

#define green redbud::io::state::manual << redbud::io::hfg::green
#define red   redbud::io::state::manual << redbud::io::hfg::red

#if defined(_MSC_VER)
#pragma warning(disable : 4244)
#pragma warning(disable : 4996)
#endif	

}

namespace test {

/**
 * @brief 测试类，用于封装单个测试案例
 * 
 */
class TestCase {
public:
	/**
	 * @brief Construct a new Test Case object
	 * 
	 * @param case_name 测试案例的名称
	 */
	TestCase(const char* case_name) : testcase_name(case_name) {}

	/**
	 * @brief 纯虚函数，用于运行测试案例
	 * 
	 */
	virtual void Run() = 0;

public:
	const char*	testcase_name;	// 测试案例的名称
	int			n_test_result;	// 测试案例的执行结果
	double		n_failed;		// 测试失败的案例数
	double		n_passed;		// 测试通过的案例数
};

/**
 * @brief 单元测试，将所有测试案例加入到vector中，依次执行案例
 * 
 */
class UnitTest {
public:
	/**
	 * @brief Get the Instance object
	 * 
	 * @return UnitTest* 
	 */
	static UnitTest* GetInstance();

	/**
	 * @brief 
	 * 
	 * @param testcase 测试案例
	 * @return TestCase* 
	 */
	TestCase* RegisterTestCase(TestCase* testcase);

	void Run();

public:
	TestCase* CurrentTestCase;			// 当前执行的测试案例
	double n_passed;					// 通过案例数
	double n_failed;					// 失败案例数

protected:
	std::vector<TestCase*> testcases_;	// 保存案例集合
	
};

UnitTest* UnitTest::GetInstance() {
	static UnitTest instance;
	return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase) {
	testcases_.push_back(testcase);
	return testcase;
}

void UnitTest::Run() {
	for (auto it : testcases_) {
		TestCase* testcase = it;
		CurrentTestCase = testcase;
		testcase->n_test_result = 1;
		testcase->n_failed = 0;
		testcase->n_passed = 0;
		std::cout << green << "================================================" << std::endl;
		std::cout << green << " Run TestCase: " << testcase->testcase_name << std::endl;
		testcase->Run();
		if (testcase->n_failed == 0)
			std::cout << green;
		else
			std::cout << red;
		std::cout << " " << testcase->n_passed << " / " << testcase->n_failed + testcase->n_passed
	  	<< " Cases passed. ( " << testcase->n_passed / 
	  	(testcase->n_failed + testcase->n_passed) * 100 << "% )\n";
		std::cout << green << " End TestCase:" << testcase->testcase_name << "\n";
		if (testcase->n_test_result)
	  	++n_passed;
		else
	  	++n_failed;
	}
	std::cout << green << "===============================================" << std::endl;
	std::cout << green << " Total TestCase : " << n_passed + n_failed << std::endl;
	std::cout << green << " Total Passed : " << n_passed << std::endl;
	std::cout << red << " Total Failed : " << n_failed << std::endl;
	std::cout << green << " " << n_passed << " / " << n_failed + n_passed
		<< " TestCases passed. ( " << n_passed / (n_failed + n_passed) * 100 << "% )" << std::endl;
}

// 测试案例的类名，替换为 testcase _name
#define TESTCASE_NAME(testcase_name) \
	testcase_name##_TEST

// 使用宏定义掩盖复杂的测试样例封装过程
#define MYTINYSTL_TEST_(testcase_name)									\
class TESTCASE_NAME(testcase_name) : public TestCase {					\
public:																	\
	TESTCASE_NAME(testcase_name)(const char* case_name)					\
		: TestCase(case_name) {};										\
	virtual void Run();													\
private:																\
	static TestCase* const testcase_;									\
};																		\
																		\
TestCase* const TESTCASE_NAME(testcase_name)							\
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase(			\
        new TESTCASE_NAME(testcase_name)(#testcase_name));				\
void TESTCASE_NAME(testcase_name)::Run()

#define EXPECT_EQ(v1, v2) do {											\
	if (v1 == v2) {														\
		UnitTest::GetInstance()->CurrentTestCase->n_passed++;			\
		std::cout << green << " EXCEPT_CON_EQ succeeded!\n";			\
	}																	\
	else {																\
		UnitTest::GetInstance()->CurrentTestCase->n_test_result = 0;	\
		UnitTest::GetInstance()->CurrentTestCase->n_failed++;			\
		std::cout << red << " EXCEPT_CON_EQ failed!\n";					\
		std::cout << red << " Except:" << v1 << "\n";					\
		std::cout << red << " Actual:" << v2 << "\n";					\
	}																	\
} while(0)

/*
容器比较
EXPECT_CON_EQ(c1, c2) 验证条件: c1 == c2
EXPECT_CON_NE(c1, c2) 验证条件: c1 != c2

Note:
1. 容器可以是 STL 容器，自定义的容器，或者数组，但不可以是指针
2. 容器的数据类型要能够进行比较，类型一致或可以发生隐式转换
3. EXPECT_CON_EQ 测试失败时，会打印首次不相等的两个值

Example:
int arr[] = {1,2,3};
std::vector<int> v1{1, 2, 3};
std::vector<int> v2{2, 3, 4};
mystl::vector<long> v3(arr, arr + 3);
EXPECT_CON_NE(v1, v2)   ok
EXPECT_CON_EQ(arr, v1)  ok
EXPECT_CON_EQ(v1, v3)   ok
*/
#define EXPECT_CON_EQ(c1, c2) do {										\
	auto first1 = std::begin(c1), last1 = std::end(c1);					\
	auto first2 = std::begin(c2), last2 = std::end(c2);					\
	for (; first1 != last1 && first2 != last2; ++first1, ++first2) {	\
		if(*first1 != *first2) break;									\
	}																	\
	if (first1 == last1 && first2 == last2) {							\
		UnitTest::GetInstance()->CurrentTestCase->n_passed++;			\
		std::cout << green << " EXCEPT_CON_EQ succeeded!\n";			\
	}																	\
	else {																\
		UnitTest::GetInstance()->CurrentTestCase->n_test_result = 0;	\
		UnitTest::GetInstance()->CurrentTestCase->n_failed++;			\
		std::cout << red << " EXCEPT_CON_EQ failed!\n";					\
		std::cout << red << " Except:" << *first1 << "\n";				\
		std::cout << red << " Actual:" << *first2 << "\n";				\
	}																	\
} while(0)


// 输出通过提示
#define PASSED	std::cout << "[ PASSED ]\n"

// 遍历输出容器
#define COUT(container) do {											\
	std::string con_name = #container;									\
	std::cout << " " << con_name << " :";								\
	for (auto it : container)											\
		std::cout << " " << it;											\
	std::cout << std::endl;												\
} while(0)

// 输出容器调用函数后的结果
#define FUN_AFTER(con, fun) do {										\
	std::string fun_name = #fun;										\
	std::cout << " After " << fun_name << " :" << std::endl;			\
	fun;																\
	COUT(con);															\
} while(0);

// 输出容器调用函数的值
#define FUN_VALUE(fun) do {												\
	std::string fun_name = #fun;										\
	std::cout << " " << fun_name << " : " << fun << std::endl;			\
} while(0)

#define TEST(testcase_name) \
	MYTINYSTL_TEST_(testcase_name)

// 运行所有测试案例
#define RUN_ALL_TESTS() \
	mystl::test::UnitTest::GetInstance()->Run()

}
}