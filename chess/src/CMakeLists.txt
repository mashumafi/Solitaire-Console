include_directories(${chess_SOURCE_DIR}/include)
add_library(chess Chess.cpp)
target_link_libraries(chess common)
