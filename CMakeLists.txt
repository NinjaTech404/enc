cmake_minimum_required(VERSION 3.10...4.1.2)

project(
  ENC
  VERSION 2.0.0
  DESCRIPTION "A simple and straight forward c++ Encode/Decode CLI toolkit for everyday use"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MAIN ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_executable(enc ${MAIN})

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/CLI)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/fmt)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/termcolor)

target_link_libraries(enc PRIVATE fmt::fmt)
target_link_libraries(enc PRIVATE termcolor)

message("This Project was made with cmake by NinjaTech404\nAlso visit https://github.com/NinjaTech404/enc")
