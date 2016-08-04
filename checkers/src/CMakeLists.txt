include_directories(${StdCpp_SOURCE_DIR}/checkers/include)
add_library(checkers Checkers.cpp)
target_link_libraries(checkers common)
