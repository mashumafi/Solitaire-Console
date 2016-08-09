include_directories(${StdCpp_SOURCE_DIR}/archive/include)
add_library(archive Archive.cpp)
target_link_libraries(archive common)
