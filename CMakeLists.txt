cmake_minimum_required(VERSION 3.20)
project(ft_malloc C)

set(CMAKE_C_STANDARD 90)

include_directories(inc)

add_executable(ft_malloc main.c src/malloc.c)
