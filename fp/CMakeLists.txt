PROJECT(fp)
add_modules(source fp)
ADD_LIBRARY(fp ${source})
TARGET_LINK_LIBRARIES(fp common)
