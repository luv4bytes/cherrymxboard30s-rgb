# CherryMXBoard30s RGB

Software for controlling RGB lighting on the    Cherry MX Board 3.0 S    for Linux.

![](doc/img/cherrymx30s_demo.gif)

I reverse engineered the USB packets that are sent to the keyboard by the official Cherry Utility software which is only available for Windows. So there is always a chance that this program might brick your device because of missing or wrong interpreted communications. So far the implemented lighting modes and effects seem to work. 

### **Use at own risk**

*This project is still WIP. Not every effect is implemented yet.*

Currently missing:
- Scan
- Custom

## Build

To build run the following:

```
mkdir -p build && cd build && cmake .. && make
```

## Usage

For viewing all possible options run the program without any arguments.

```
./cherrymxboard30s-rgb
```