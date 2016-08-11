project(archive)
add_modules(source Archive Directory File Header)
add_library(archive ${source})
target_link_libraries(archive common ${Boost_LIBRARIES})
