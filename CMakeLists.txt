# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Cat_Robot_V2 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Cat_Robot_V2 Cat_Robot_V2.c )

pico_set_program_name(Cat_Robot_V2 "Cat_Robot_V2")
pico_set_program_version(Cat_Robot_V2 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Cat_Robot_V2 1)
pico_enable_stdio_usb(Cat_Robot_V2 1)

pico_generate_pio_header(Cat_Robot_V2 ${CMAKE_CURRENT_LIST_DIR}/SPIPIO.pio)

target_sources(Cat_Robot_V2 PRIVATE Cat_Robot_V2.c TFTMaster.c glcdfont.c)

# Add the standard library to the build
target_link_libraries(Cat_Robot_V2 pico_stdlib pico_bootsel_via_double_reset pico_multicore hardware_pwm hardware_dma hardware_irq hardware_adc hardware_i2c hardware_pio)

# Add the standard include files to the build
target_include_directories(Cat_Robot_V2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# add_executable(Cat_Robot)

# # must match with pio filename and executable name from above

# pico_generate_pio_header(Cat_Robot ${CMAKE_CURRENT_LIST_DIR}/vsync.pio)
# pico_generate_pio_header(Cat_Robot ${CMAKE_CURRENT_LIST_DIR}/rgb.pio)
# # must match with executable name and source file names

# create map/bin/hex file etc.
pico_add_extra_outputs(Cat_Robot_V2)

