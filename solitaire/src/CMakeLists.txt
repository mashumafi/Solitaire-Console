include_directories(${StdCpp_SOURCE_DIR}/solitaire/include)
add_library(solitaire Solitaire.cpp)
target_link_libraries(solitaire common)
