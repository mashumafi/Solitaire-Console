project(chess)
add_modules(source Chess)
add_library(chess ${source})
target_link_libraries(chess common)
