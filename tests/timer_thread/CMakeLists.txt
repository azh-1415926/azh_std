cmake_minimum_required(VERSION 2.8.0)
project(timer_thread)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} AZH_Library)