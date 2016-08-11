PROJECT(common)
add_modules(source Card Deck Grid Main Piece Hand Player Random)
ADD_LIBRARY(common ${source})
