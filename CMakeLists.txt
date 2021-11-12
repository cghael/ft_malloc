cmake_minimum_required(VERSION 3.20)
project(ft_malloc C)

set(CMAKE_C_STANDARD 90)

include_directories(inc)

add_executable(ft_malloc main.c src/malloc.c src/ft_find_block_size.c src/ft_get_new_zone_size.c src/free.c src/realloc.c src/utilits.c src/calloc.c src/show_alloc_mem.c src/ft_memory_allocation.c src/ft_free_small_zone.c src/ft_unite_with_next.c)
