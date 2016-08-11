PROJECT(irc)
add_modules(source IRCClient)
ADD_LIBRARY(irc ${source})
TARGET_LINK_LIBRARIES(irc common ${Boost_LIBRARIES})
