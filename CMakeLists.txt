cmake_minimum_required(VERSION 3.5.1)
project(instant)

set(CMAKE_CXX_STANDARD 14)

include_directories(./src)

add_library(Parser ${CMAKE_SOURCE_DIR}/src/Parser.cpp)
add_library(Printer ${CMAKE_SOURCE_DIR}/src/Printer.cpp)
add_library(Lexer ${CMAKE_SOURCE_DIR}/src/Lexer.cpp)
add_library(Absyn ${CMAKE_SOURCE_DIR}/src/Absyn.cpp)

add_executable(Instant ${CMAKE_SOURCE_DIR}/src/Test.cpp)
target_link_libraries(Instant Parser Printer Lexer Absyn)