cmake_minimum_required(VERSION 3.20)
project(ft_malloc C)

set(CMAKE_C_STANDARD 90)

include_directories(inc)

add_executable(ft_malloc main.c src/malloc.c src/ft_find_block_size.c src/get_malloc_manager.c src/ft_get_new_zone_size.c src/free.c)
