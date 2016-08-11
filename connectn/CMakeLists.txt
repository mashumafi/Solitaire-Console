PROJECT(connectn)
add_modules(source ConnectN)
ADD_LIBRARY(connectn ${source})
TARGET_LINK_LIBRARIES(connectn common)
