# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(I2C1-OLDE C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()
# Add Subdirectory
add_subdirectory(./examples)
add_subdirectory(./lib/Config)
add_subdirectory(./lib/OLED)
add_subdirectory(./lib/Fonts)
add_subdirectory(./lib/GUI)

# Include Directories
include_directories(./examples)
include_directories(./lib/Config)
include_directories(./lib/OLED)
include_directories(./lib/Fonts)
include_directories(./lib/GUI)

# Add executable. Default name is the project name, version 0.1

add_executable(OLED_0in49 OLED_0in49.c )

pico_set_program_name(OLED_0in49 "OLED_0in49")
pico_set_program_version(OLED_0in49 "0.1")

pico_enable_stdio_uart(OLED_0in49 1)
pico_enable_stdio_usb(OLED_0in49 0)

# Add the standard library to the build
target_link_libraries(OLED_0in49 pico_stdlib examples Config GUI Fonts OLED hardware_spi hardware_i2c hardware_pwm hardware_adc)

pico_add_extra_outputs(OLED_0in49)

