PROJECT(meta)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

add_library(meta STATIC include/fib.hpp)
set_target_properties(meta PROPERTIES LINKER_LANGUAGE CXX)
