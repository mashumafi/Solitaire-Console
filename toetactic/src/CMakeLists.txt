include_directories(${toetactic_SOURCE_DIR}/include)
add_library(toetactic ToeTacTic.cpp)
target_link_libraries(toetactic common)
