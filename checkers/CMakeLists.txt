project(checkers)
add_modules(source Checkers)
add_library(checkers ${source})
target_link_libraries(checkers common)
