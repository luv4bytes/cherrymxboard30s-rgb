# CherryMXBoard30s RGB

Software for controlling RGB lighting on the *Cherry MX Board 3.0 S*    for Linux.

![](doc/img/cherrymx30s_demo.gif)

I reverse engineered the USB packets that are sent to the keyboard by the official Cherry Utility software which is only available for Windows. So there is always a chance that this program might brick your device because of missing or wrong interpreted communications. So far the implemented lighting modes and effects seem to work. 

### <span style="color:red">***Use at own risk***</span>

*This project is still WIP. Not every effect is implemented yet.*

Currently missing:
- Scan
- Custom

### Tested on:
Ubuntu 20.04  
Ubuntu 21.10

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