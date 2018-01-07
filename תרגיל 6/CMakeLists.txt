cmake_minimum_required(VERSION 3.8)
project(_6)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c game.c person.c sorting.c utils.c)
add_executable(_6 ${SOURCE_FILES})