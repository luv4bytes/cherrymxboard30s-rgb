# CherryMXBoard30s RGB

[![Ubuntu 20.04 Build](https://github.com/luv4bytes/cherrymxboard30s-rgb/actions/workflows/ubuntu-20.04.yml/badge.svg)](https://github.com/luv4bytes/cherrymxboard30s-rgb/actions/workflows/ubuntu-20.04.yml)
[![Ubuntu 22.04 Build](https://github.com/luv4bytes/cherrymxboard30s-rgb/actions/workflows/ubuntu-22.04.yml/badge.svg)](https://github.com/luv4bytes/cherrymxboard30s-rgb/actions/workflows/ubuntu-22.04.yml)

Please consider using [cherryrgb-rs](https://github.com/skraus-dev/cherryrgb-rs) by [@Sebastian Kraus](https://github.com/skraus-dev) for a more robust and versatile solution.

Software for controlling RGB lighting on the *Cherry MX Board 3.0 S*    for Linux.

![](doc/img/cherrymx30s_demo.gif)

I reverse engineered the USB packets that are sent to the keyboard by the official Cherry Utility software which is only available for Windows. So there is always a chance that this program might brick your device because of missing or wrong interpreted communications. So far the implemented lighting modes and effects seem to work.

### <span style="color:red">***Use at own risk***</span>

*This project is still WIP. Not every effect is implemented yet.*

Currently missing:

- Custom

### Tested on

- Ubuntu 20.04  
- Ubuntu 21.10
- Ubuntu 22.04

## Build & Install

### Requirements

- libusb-1.0-0
- libusb-1.0-0-dev

```
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE={BuildType} ..

# For a simple build
make

# For installing
sudo make install

```

The easiest and recommended way to install is using *sudo make install*.

## Usage

To display the program help you need to run the program without any further arguments.

```
./cherrymxboard30s-rgb
```

### Examples

```
# Setting the keyboard to static red light with full brightness.

./cherrymxboard30s-rgb -l static --red 255 -b 4


# Setting the keybord to wave light with random colors and full speed.

./cherrymxboard30s-rgb -l wave -r -b 4 -s 0


# Setting keyboard device and vendor id.

./cherrymxboard30-rgb -l static --blue 255 --vendor-id 0x0001 --product-id 0x0002
```
