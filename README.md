# [WIP] SPI Flash driver for Pi PIco
**Device:** W25Q128

**Datasheet** : https://www.pjrc.com/teensy/W25Q128FV.pdf

Current setup is for use over USB serial

1. Run the pico
2. `screen /dev/cu.usbmodemXXXX`
3. Inputs: `q` = reboot to flash, `r` = enable write and read status register 1. Any other entrance is nothing.

Update: Now I've figured out writing! Hip-hip-hooray!
