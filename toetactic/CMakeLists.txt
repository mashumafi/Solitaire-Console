project(toetactic)
add_modules(source ToeTacTic)
add_library(toetactic ${source})
target_link_libraries(toetactic common)
