PROJECT(tetris)
add_modules(source Tetris)
ADD_LIBRARY(tetris ${source})
TARGET_LINK_LIBRARIES(tetris common)
