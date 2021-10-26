cmake_minimum_required(VERSION 3.20)
project(Progetto C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Progetto
        main.c
        set.c
        set.h
        subset_construction.c
        subset_construction.h)
