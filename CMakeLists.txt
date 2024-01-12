cmake_minimum_required(VERSION 3.10)
project(test_project VERSION 1.0.0)

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# #
set(CMAKE_BUILD_TYPE Debug)

# 添加头文件路径    
SET(test_project_INC   
${PROJECT_SOURCE_DIR}/include
${PROJECT_SOURCE_DIR}/include/easylogger/src
${PROJECT_SOURCE_DIR}/include/easylogger/port
)
INCLUDE_DIRECTORIES(${test_project_INC})
message(test_project_INC)

get_property(dirs DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(">>> include_dirs=${dirs}")

# 向环境中添加库文件搜索路径
link_directories("${PROJECT_SOURCE_DIR}/libs")
link_libraries("${PROJECT_SOURCE_DIR}/libs/libHR_Pro.so")

#设置生成的可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#源码工程和测试工程
add_subdirectory(src)
