PROJECT(archive)
add_modules(source Archive ArchiveUtil Available Directory File Header Meta StreamWrapper)
ADD_LIBRARY(archive ${source})
TARGET_LINK_LIBRARIES(archive common ${Boost_LIBRARIES})
