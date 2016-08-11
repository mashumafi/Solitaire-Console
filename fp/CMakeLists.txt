project(fp)
add_modules(source fp)
add_library(fp ${source})
target_link_libraries(fp common)

