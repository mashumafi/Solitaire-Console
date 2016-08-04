include_directories(${StdCpp_SOURCE_DIR}/toetactic/include)
add_library(toetactic ToeTacTic.cpp)
target_link_libraries(toetactic common)
