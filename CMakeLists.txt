cmake_minimum_required(VERSION 3.10)

project(blink)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLAD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad")
set(GLFW_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw")
set(GLM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm")

add_subdirectory(${GLAD_PATH} ${CMAKE_BINARY_DIR}/glad)
add_subdirectory(${GLFW_PATH} ${CMAKE_BINARY_DIR}/glfw)
add_subdirectory(${GLM_PATH} ${CMAKE_BINARY_DIR}/glm)

# stb
add_library(stb STATIC dependencies/stb/stb_image.cpp)
target_include_directories(stb PUBLIC dependencies/stb)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
		src/*.cpp
		src/components/*.cpp
		src/systems/*.cpp
		src/factories/*.cpp
		src/utils/*.cpp
)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
		src/*.hpp
		src/components/*.hpp
		src/systems/*.hpp
		src/factories/*.hpp
		src/utils/*.hpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glm)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glad)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC stb)
