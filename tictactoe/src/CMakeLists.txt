include_directories(${StdCpp_SOURCE_DIR}/tictactoe/include)
add_library(tictactoe TicTacToe.cpp)
target_link_libraries(tictactoe common)
