# Find Zephyr. This also loads Zephyr's build system.
cmake_minimum_required(VERSION 3.13.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Temporarly select nucleo board
set(BOARD nucleo_l432kc)

# set(ZEPHYR_MODULES "~/dev/projects/zephyr_module_test")

find_package(Zephyr)
project(zephyr_playground)

# Add your source file to the "app" target. This must come after
# find_package(Zephyr) which defines the target.
target_sources(app PRIVATE src/main.c)

add_subdirectory(drivers)

