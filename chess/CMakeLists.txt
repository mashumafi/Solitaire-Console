PROJECT(chess)
add_modules(source Chess)
ADD_LIBRARY(chess ${source})
TARGET_LINK_LIBRARIES(chess common)
