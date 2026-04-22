cmake_minimum_required(VERSION 3.22.1)

project("monjnidemo")

add_library(
        securite-lib
        SHARED
        detection.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        securite-lib
        ${log-lib})