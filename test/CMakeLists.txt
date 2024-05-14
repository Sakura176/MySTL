# 使用 GTest 框架
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# 添加项目源文件
include_directories(${PROJECT_SOURCE_DIR}/MySTL)

# 添加测试文件
add_executable(algorithm_test	algorithm_test.cpp)
add_executable(vector_test		vector_test.cpp)
add_executable(string_test		string_test.cpp)


# 链接 GTest 库和你的源文件
target_link_libraries(vector_test PRIVATE GTest::GTest GTest::Main pthread)
target_link_libraries(string_test PRIVATE GTest::GTest GTest::Main pthread)
target_link_libraries(algorithm_test PRIVATE GTest::GTest GTest::Main pthread)

# 分组测试用例
# set_tests_properties(stl_test PROPERTIES LABELS "Algorithm;Iterator;Vector;List;String")

# 添加测试
add_test(NAME algorithm_test COMMAND algorithm_test)
add_test(NAME vector_test COMMAND vector_test)
add_test(NAME string_test COMMAND string_test)


# include(GoogleTest)
# gtest_add_tests(TARGET stl_test)

# gtest_discover_tests(stl_test
#                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
#                      PROPERTIES LABELS 
#                      )

# gtest_discover_tests(string_test
#                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
#                      PROPERTIES LABELS 
#                      )
