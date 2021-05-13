hc12_custom_firmware

# SDCC and stm8flash installation for Linux

To install SDCC on linux (Ubuntu) simply use: `apt install sdcc`

To install stm8flash run:
```bash
git clone https://github.com/vdudouyt/stm8flash.git
cd stm8flash
make
sudo make install
```

# STM8 Standard Peripherals Library

The library adapted for SDCC can be found [here](https://github.com/roshbaby/stm8s-sdcc).