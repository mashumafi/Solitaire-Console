project(blackjack)
add_modules(source Blackjack)
add_library(blackjack ${source})
target_link_libraries(blackjack common)
