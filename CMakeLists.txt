# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(jnecalc)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(jnecalc sources/jnecalc.cpp)

target_link_libraries(jnecalc ${GTK3_LIBRARIES})
