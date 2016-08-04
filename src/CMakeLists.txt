include_directories(${MyProject_SOURCE_DIR}/solitaire/include)
link_directories(${MyProject_SOURCE_DIR}/solitaire/src)
add_executable(solitaire solitaire.cpp)
target_link_libraries(solitaire solitaire)
