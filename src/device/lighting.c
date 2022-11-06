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

#include "stdlib.h"

#include "lighting.h"

static char* LIGHTING_MODE_STRS[] = {
    "Wave",
    "Spectrum",
    "Breating",
    "Rolling",
    "Curve",
    "Scan",
    "Custom",
    "Radiation",
    "Ripples",
    "Single key",
    "Static",
};

void lighting_init(lighting_t* lighting)
{
    if (lighting == NULL)
    {
        return;
    }

    lighting->red = 0;
    lighting->green = 0;
    lighting->blue = 0;

    lighting->mode = STATIC;

    lighting->speed = 4;
    lighting->brightness = 4;
    lighting->random_colors = false;
}

char* lighting_mode_str(LMODE mode)
{
    return LIGHTING_MODE_STRS[mode];
}