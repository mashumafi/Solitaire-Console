include_directories(${StdCpp_SOURCE_DIR}/archive/include)
include_directories(${StdCpp_SOURCE_DIR}/solitaire/include)
add_executable(lobby lobby.cpp)
target_link_libraries(lobby archive blackjack checkers chess connectn solitaire tictactoe toetactic)
