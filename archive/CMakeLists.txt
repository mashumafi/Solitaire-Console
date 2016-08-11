PROJECT(archive)
add_modules(source Archive Directory File Header)
ADD_LIBRARY(archive ${source})
TARGET_LINK_LIBRARIES(archive common ${Boost_LIBRARIES})
