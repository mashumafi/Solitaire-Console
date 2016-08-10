include_directories(${tictactoe_SOURCE_DIR}/include)
add_library(tictactoe TicTacToe.cpp)
target_link_libraries(tictactoe common)
