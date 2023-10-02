cmake_minimum_required(VERSION 3.1)

project(MySTL)

# build type
set(CMAKE_BUILD_TYPE Debug)

# 添加可选的宏定义，根据构建类型设置
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# -Wno-unused-but-set-variable
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -O2 -g -Wall -Wextra -Wno-sign-compare -Wno-array-bounds")
	# set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wsign-conversion)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0")
		message(FATAL_ERROR "required GCC 5.0 or later")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare")
	# set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wimplicit-fallthrough)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")
		message(FATAL_ERROR "required Clang 3.5 or later")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/test)