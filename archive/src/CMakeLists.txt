include_directories(${archive_SOURCE_DIR}/include)
add_library(archive Archive.cpp Directory.cpp File.cpp Header.cpp)
target_link_libraries(archive common)
