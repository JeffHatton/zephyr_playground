# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

# zephyr_library()

message("tset")
target_sources(app PRIVATE testDevice.c)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# zephyr_library_sources(PUBLIC testDevice.c)
# zephyr_library_include_directories(PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})
 