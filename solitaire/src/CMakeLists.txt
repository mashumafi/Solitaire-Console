include_directories(${solitaire_SOURCE_DIR}/include)
add_library(solitaire Solitaire.cpp)
target_link_libraries(solitaire common)
