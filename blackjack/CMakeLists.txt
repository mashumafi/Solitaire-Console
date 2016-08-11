PROJECT(blackjack)
add_modules(source Blackjack)
ADD_LIBRARY(blackjack ${source})
TARGET_LINK_LIBRARIES(blackjack common)
