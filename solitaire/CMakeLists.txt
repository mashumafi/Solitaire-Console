PROJECT(solitaire)
add_modules(source Solitaire)
ADD_LIBRARY(solitaire ${source})
TARGET_LINK_LIBRARIES(solitaire common)
TARGET_INCLUDE_DIRECTORIES(solitaire PUBLIC include)
