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

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

/**
 * @brief Defines how colors are displayed on the keyboard. I.e. STATIC, WAVE, BREATHING, CURVE etc.
 *
 */
typedef enum
{
    WAVE = 0,
    SPECTRUM = 1,
    BREATHING = 2,
    ROLLING = 3,
    CURVE = 4,
    SCAN = 5,
    CUSTOM = 6,
    RADIATION = 7,
    RIPPLES = 8,
    SINGLE_KEY = 9,
    STATIC = 10,

} LIGHTING;

/**
 * @brief Defines lighting information.
 *
 */
typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    LIGHTING lighting;

    uint8_t speed;
    uint8_t brightness;
    bool random_colors;

} lighting_t;

/**
 * @brief Initializes the given lighting.
 *
 * @param lighting Holds information about lighting.
 */
void lighting_init(lighting_t* lighting);