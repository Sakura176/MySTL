# 使用 GTest 框架
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# 添加项目源文件
include_directories(${PROJECT_SOURCE_DIR}/MySTL)

# 添加测试文件
add_executable(stl_test 
	algorithm_test.cpp
	vector_test.cpp
	list_test.cpp
)

# 链接 GTest 库和你的源文件
target_link_libraries(stl_test PRIVATE GTest::GTest GTest::Main pthread)

# 添加测试
include(GoogleTest)
gtest_add_tests(TARGET stl_test)
