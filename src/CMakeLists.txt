cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(w25q128_driver)

set(CMAKE_C_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(w25q128_driver
	main.c
)



target_include_directories(w25q128_driver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(w25q128_driver
	pico_stdlib 
	hardware_spi
	hardware_pwm
	hardware_gpio
	pico_bootrom)

pico_enable_stdio_usb(w25q128_driver 1)
pico_enable_stdio_uart(w25q128_driver 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(w25q128_driver)

