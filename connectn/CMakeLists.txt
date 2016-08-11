project(connectn)
add_modules(source ConnectN)
add_library(connectn ${source})
target_link_libraries(connectn common)
