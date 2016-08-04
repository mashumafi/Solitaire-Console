include_directories(${StdCpp_SOURCE_DIR}/connectn/include)
add_library(connectn ConnectN.cpp)
target_link_libraries(connectn common)
