include_directories(${StdCpp_SOURCE_DIR}/chess/include)
add_library(chess Chess.cpp)
target_link_libraries(chess common)
