add_subdirectory(core)

add_executable(blink main.cpp)

target_link_libraries(blink PRIVATE core glfw glad)