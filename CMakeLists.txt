cmake_minimum_required(VERSION 4.3)
project(game C)

set(CMAKE_C_STANDARD 17)

add_executable(game main.c
        includes/entity.h
        includes/entity.c)

target_compile_definitions(game PRIVATE
        DEBUG)