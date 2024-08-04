cmake_minimum_required(VERSION 3.10)

project(blink)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置第三方库的路径
set(GLFW_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw")
set(GLAD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad")

# 添加第三方库
add_subdirectory(${GLFW_PATH} ${CMAKE_BINARY_DIR}/glfw)
add_subdirectory(${GLAD_PATH} ${CMAKE_BINARY_DIR}/glad)


add_subdirectory(src)
