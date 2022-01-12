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
    printf("\033[36mcherry-mx-board_3_0s-rgb\033[0m\n");
    printf("\n");
    printf("Usage: ./cherry-mx-board_3_0s-rgb [OPTIONS...] [LIGHTING] \033[0m\n");
    printf("\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--red", "[0 - 255]", "Red value of the RGB value that shall be used for setting the color.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--green", "[0 - 255]", "Green value of the RGB value that shall be used for setting the color.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--blue", "[0 - 255]", "Blue value of the RGB value that shall be used for setting the color.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "-l", "--lighting", "[LIGHT MODE]", "The way of displaying the color on the keyboard. I.e. STATIC, WAVE, CURVE etc.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-s", "--speed", "[0 - 4]", "Speed of the lighting. Ranges from 0 (fastest) to 4 (slowest).\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-r", "--random-colors", "", "Applies random colors for lighting if applicable.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--vendor-id", "[VENDOR]", "Specifies an explicit vendor id to look for when searching for the device. If not specified standard value is set.\n");
    printf("%-5s%-10s%-20s\t%s\t%s", " ", "", "--product-id", "[PRODUCT]", "Specifies an explicit product id to look for when searching for the device. If not specified standard value is set.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "-v", "--verbose", "", "Verbose outout. Including libusb debug messages.\n");
    printf("%-5s%-10s%-20s\t%s\t\t%s", " ", "", "--version", "", "Prints the version number.\n");
    printf("\n");
    printf("Remarks: Using cherry-mx-board_3_0s-rgb requires sudo permissions. Otherwise use udev.\n");
    printf("For more information see \033[35mhttps://github.com/luv4bytes/cherry-mx-board_3_0s-rgb\033[0m.\n");
    printf("\n");
}

void version_print()
{
    printf("%s\n", VERSION);
}
