include_directories(${StdCpp_SOURCE_DIR}/solitaire/include)
link_directories(${StdCpp_SOURCE_DIR}/solitaire/src)
add_executable(game solitaire.cpp)
target_link_libraries(game solitaire)
