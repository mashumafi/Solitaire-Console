include_directories(${StdCpp_SOURCE_DIR}/blackjack/include)
add_library(blackjack Blackjack.cpp)
target_link_libraries(blackjack common)
