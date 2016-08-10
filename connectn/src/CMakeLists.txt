include_directories(${connectn_SOURCE_DIR}/include)
add_library(connectn ConnectN.cpp)
target_link_libraries(connectn common)
