cmake_minimum_required(VERSION 3.6...3.14 FATAL_ERROR)
cmake_policy(VERSION 3.6...3.14)

# 从 version.hpp 中获取版本信息
file(READ "include/azh/version.hpp" AZH_VERSION_FILE)
string(REGEX MATCH "#define[ ]+AZH_VERSION_MAJOR[ ]+([0-9]+)" _ ${AZH_VERSION_FILE})
set(AZH_VERSION_MAJOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+AZH_VERSION_MINOR[ ]+([0-9]+)" _ ${AZH_VERSION_FILE})
set(AZH_VERSION_MINOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+AZH_VERSION_PATCH[ ]+([0-9]+)" _ ${AZH_VERSION_FILE})
set(AZH_VERSION_PATCH "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+AZH_VERSION_REVISION[ ]+([0-9]+)" _ ${AZH_VERSION_FILE})
set(AZH_VERSION_REVISION "${CMAKE_MATCH_1}")

set(AZH_VERSION ${AZH_VERSION_MAJOR}.${AZH_VERSION_MINOR}.${AZH_VERSION_PATCH})

# 设置项目版本
project(azh_std VERSION ${AZH_VERSION} LANGUAGES CXX)
message(STATUS "azh_std : version " ${AZH_VERSION})

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE incs ${CMAKE_SOURCE_DIR}/include/*.h*)
file(GLOB_RECURSE srcs ${CMAKE_SOURCE_DIR}/src/*.c*)

add_library(AZH_Library ${incs} ${srcs})

target_include_directories(AZH_Library PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(
	DIRECTORY include
	DESTINATION "."
    # PATTERN "CMakeLists.txt" EXCLUDE    
)

install(TARGETS AZH_Library
    EXPORT AZH_Library-targets
    PUBLIC_HEADER DESTINATION include
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(EXPORT AZH_Library-targets
    NAMESPACE AZH_Library::
    FILE AZH_Library-Target.cmake
    DESTINATION lib/cmake/AZH_Library)

include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/AZH_Library-Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/AZH_Library-Config.cmake
        INSTALL_DESTINATION lib/cmake
        )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AZH_Library-Config.cmake DESTINATION lib/cmake/AZH_Library)

add_subdirectory(tests)