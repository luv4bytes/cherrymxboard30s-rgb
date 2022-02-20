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

#pragma once

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "getopt.h"
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

#include "../help/help.h"
#include "../device/lighting.h"

/**
 * @brief Defines the application arguments.
 */
typedef struct {

    /**
     * @brief Red part of the RGB value to set.
     *
     */
    u_int8_t red;

    /**
     * @brief Red part of the RGB value to set.
     *
     */
    u_int8_t green;

    /**
     * @brief Red part of the RGB value to set.
     *
     */
    u_int8_t blue;

    /**
     * @brief The way of displaying the color on the keyboard. I.e. STATIC, WAVE, CURVE etc.
     *
     */
    LMODE lighting;

    /**
     * @brief Speed for keyboard lighting.
     *
     */
    uint8_t speed;

    /**
     * @brief Speed for keyboard lighting.
     *
     */
    uint8_t brightness;

    /**
     * @brief Determines if random colors should be used. If this is true explicit RGB values are ignored.
     *
     */
    bool random_colors;

    /**
     * @brief Explicit vendor id.
     *
     */
    int vendor_id;

    /**
     * @brief Explicit product id.
     *
     */
    int product_id;

    /**
     * @brief Defines if the application should be run in verbose mode.
     */
    bool verbose;

} args_t;

/**
 * @brief Initializes the given args.
 *
 * @param args The args that need to be initialized.
 */
void args_init(args_t* args);

/**
 * @brief Parses the given arguments and sets the values in args.
 *
 * @param argc Argument counter.
 * @param argv Arguments.
 * @param args Pointer to args_t struct holding the argument values.
 */
void args_parse(int argc, char** argv, args_t* args);
