include_directories(${blackjack_SOURCE_DIR}/include)
add_library(blackjack Blackjack.cpp)
target_link_libraries(blackjack common)
