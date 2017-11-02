cmake_minimum_required(VERSION 3.5.1)
project(instant)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(Parser ${CMAKE_SOURCE_DIR}/src/Parser.cpp)
add_library(Printer ${CMAKE_SOURCE_DIR}/src/Printer.cpp)
add_library(Lexer ${CMAKE_SOURCE_DIR}/src/Lexer.cpp)
add_library(Absyn ${CMAKE_SOURCE_DIR}/src/Absyn.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/jvm_instant)
add_library(Result ${CMAKE_SOURCE_DIR}/src/jvm_instant/Result.cpp)
add_library(JVMVisitor ${CMAKE_SOURCE_DIR}/src/jvm_instant/JvmVisitor.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/llvm_instant)
add_library(LLVMVisitor ${CMAKE_SOURCE_DIR}/src/llvm_instant/LlvmVisitor.cpp)

add_executable(insc_jvm ${CMAKE_SOURCE_DIR}/src/jvm_instant/JvmInstant.cpp)
target_link_libraries(insc_jvm Parser Printer Lexer Absyn JVMVisitor Result)