cmake_minimum_required(VERSION 3.25)
project(Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project2
        chatBot.c
        chatBot.h src/linked_list.c src/file_handler.c src/io.c src/string_handler.c)
