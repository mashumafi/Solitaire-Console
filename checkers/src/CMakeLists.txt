include_directories(${checkers_SOURCE_DIR}/include)
add_library(checkers Checkers.cpp)
target_link_libraries(checkers common)
