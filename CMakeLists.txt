cmake_minimum_required(VERSION 2.8)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

project(StdCpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${StdCpp_SOURCE_DIR})
include_directories(${StdCpp_SOURCE_DIR}/common/include)

add_subdirectory(common)
add_subdirectory(archive)
add_subdirectory(blackjack)
add_subdirectory(checkers)
add_subdirectory(chess)
add_subdirectory(connectn)
add_subdirectory(solitaire)
add_subdirectory(sqlite)
add_subdirectory(tictactoe)
add_subdirectory(toetactic)
add_subdirectory(src)
