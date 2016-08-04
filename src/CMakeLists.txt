include_directories(${StdCpp_SOURCE_DIR}/solitaire/include)
add_executable(lobby lobby.cpp)
target_link_libraries(lobby solitaire)
