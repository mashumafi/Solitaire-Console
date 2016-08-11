cmake_minimum_required(VERSION 2.8)

project(TerminalCPP)
set(CMAKE_MODULE_PATH ${TerminalCPP_SOURCE_DIR}/cmake_modules)

if(UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(functions)

if(WIN32)
  add_definitions(-DBOOST_ALL_NO_LIB)
  set(Boost_USE_STATIC_LIBS   ON)
else()
  set(Boost_USE_STATIC_LIBS  OFF)
endif()
set(Boost_USE_MULTITHREADED   ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system thread regex filesystem serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(common)
add_subdirectory(archive)
add_subdirectory(blackjack)
add_subdirectory(checkers)
add_subdirectory(chess)
add_subdirectory(connectn)
add_subdirectory(fp)
add_subdirectory(solitaire)
add_subdirectory(sqlite)
add_subdirectory(tictactoe)
add_subdirectory(toetactic)
add_subdirectory(src)
