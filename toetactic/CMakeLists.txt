PROJECT(toetactic)
add_modules(source ToeTacTic)
ADD_LIBRARY(toetactic ${source})
TARGET_LINK_LIBRARIES(toetactic common)
