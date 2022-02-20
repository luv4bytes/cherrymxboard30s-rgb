/*
MIT License

Copyright (c) 2022 Lukas Pfeifer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "help.h"

void help_print()
{
    printf(CYAN("cherrymxboard30s-rgb")"\n");
    printf("\n");
    printf(YELLOW("Usage: ./cherrymxboard30s-rgb [OPTIONS...] [LIGHTING]")"\n");
    printf("\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--red", "[0 - 255]", "Red value of the RGB value that shall be used for setting the color.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--green", "[0 - 255]", "Green value of the RGB value that shall be used for setting the color.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--blue", "[0 - 255]", "Blue value of the RGB value that shall be used for setting the color.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "-l", "--lighting", "[LIGHT MODE]", "The way of displaying the color on the keyboard. I.e. STATIC, WAVE, CURVE etc.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-s", "--speed", "[0 - 4]", "If applicable this sets the lighting effect speed. Ranges from 0 (fastest) to 4 (slowest).\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-b", "--brightness", "[1 - 4]", "Sets the brightness of the lighting.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-r", "--random-colors", "", "Applies random colors for lighting if applicable.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--vendor-id", "[VENDOR]", "Specifies an explicit vendor id to look for when searching for the device. If not specified standard value is set.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--product-id", "[PRODUCT]", "Specifies an explicit product id to look for when searching for the device. If not specified standard value is set.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-v", "--verbose", "", "Verbose outout. Including libusb debug messages.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "", "--version", "", "Prints the version number.\n");
    printf("\n");
    printf("Possible lighting modes:\n");
    printf("\n");
    printf("%-10s%-20s\n", " ", "WAVE");
    printf("%-10s%-20s\n", " ", "SPECTRUM");
    printf("%-10s%-20s\n", " ", "BREATHING");
    printf("%-10s%-20s\n", " ", "ROLLING");
    printf("%-10s%-20s\n", " ", "CURVE");
    printf("%-10s%-20s\n", " ", "SCAN");
    printf("%-10s%-20s\n", " ", "CUSTOM");
    printf("%-10s%-20s\n", " ", "RADIATION");
    printf("%-10s%-20s\n", " ", "RIPPLES");
    printf("%-10s%-20s\n", " ", "SINGLE_KEY");
    printf("%-10s%-20s\n", " ", "STATIC");
    printf("\n");
    printf("Remarks: Using cherrymxboard30s-rgb requires sudo permissions if no udev rules are defined.\n");
    printf("For more information see " GREEN("https://gitlab.com/luv4bytes/cherrymxboard30s-rgb.")"\n");
    printf("\n");
}

void version_print()
{
    printf("%s\n", VERSION);
}
