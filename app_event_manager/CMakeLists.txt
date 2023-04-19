#
# Copyright (c) 
#
# SPDX-License-Identifier: LicenseRef-
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project("app")

# Include application event headers
zephyr_library_include_directories(src/events)

target_include_directories(app PRIVATE src/events)

# Application sources
target_sources(app PRIVATE src/main.c)

file(GLOB SRC_EVENTS "src/events/*.c")
target_sources(app PRIVATE ${SRC_EVENTS})

file(GLOB SRC_MODULES "src/modules/*.c")
target_sources(app PRIVATE ${SRC_MODULES})

#target_sources(app PRIVATE
#               src/events/ack_event.c
#               src/events/config_event.c
#               src/events/control_event.c
#               src/events/measurement_event.c
#)

#target_sources(app PRIVATE
#		src/modules/controller.c
#		src/modules/sensor_simulated.c
#		src/modules/stats.c
#)
