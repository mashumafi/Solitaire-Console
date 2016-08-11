PROJECT(tictactoe)
add_modules(source TicTacToe)
ADD_LIBRARY(tictactoe ${source})
TARGET_LINK_LIBRARIES(tictactoe common)
