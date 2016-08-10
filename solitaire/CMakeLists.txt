project(solitaire)
add_modules(source Solitaire)
add_library(solitaire ${source})
target_link_libraries(solitaire common)
