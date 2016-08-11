project(irc)
add_modules(source IRCClient)
add_library(irc ${source})
target_link_libraries(irc common ${Boost_LIBRARIES})
