cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_SDK_FETCH_FROM_GIT on)

include(pico_sdk_import.cmake)

project(aoc_2024)

pico_sdk_init()

# TODO: make this easy to write a command for to build different days
add_executable(aoc_2024
	solutions/test.c
)

target_link_libraries(aoc_2024 pico_stdlib)

pico_enable_stdio_usb(aoc_2024 1)
pico_enable_stdio_uart(aoc_2024 0)

pico_add_extra_outputs(aoc_2024)
