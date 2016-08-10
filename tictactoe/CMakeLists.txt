project(tictactoe)
add_modules(source TicTacToe)
add_library(tictactoe ${source})
target_link_libraries(tictactoe common)
