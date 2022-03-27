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

#include "args.h"

static int red;
static int green;
static int blue;

static int vendor_id;
static int product_id;

static int version;

/**
 * @brief Converts the given ASCII string with given length to lower case.
 *
 * @param str The string to convert.
 * @param len The length of the string.
 */
static void astrlow(char* str, size_t len)
{
    if (str == NULL)
    {
        return;
    }

    if (len == 0)
    {
        return;
    }

    for (size_t i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }
}

/**
 * @brief Parses the lighting argument.
 *
 * @param lighting Lighting string.
 * @return LMODE Corresponding lighting value.
 */
static LMODE parse_lighting(char* lighting)
{
    if (lighting == NULL) {
        return STATIC;
    }

    astrlow(lighting, strlen(lighting));

    if (strcmp(lighting, "wave") == 0)
    {
        return WAVE;
    }

    if (strcmp(lighting, "spectrum") == 0)
    {
        return SPECTRUM;
    }

    if (strcmp(lighting, "breathing") == 0)
    {
        return BREATHING;
    }

    if (strcmp(lighting, "rolling") == 0)
    {
        return ROLLING;
    }

    if (strcmp(lighting, "curve") == 0)
    {
        return CURVE;
    }

    if (strcmp(lighting, "scan") == 0)
    {
        return SCAN;
    }

    if (strcmp(lighting, "custom") == 0)
    {
        return CUSTOM;
    }

    if (strcmp(lighting, "radiation") == 0)
    {
        return RADIATION;
    }

    if (strcmp(lighting, "ripples") == 0)
    {
        return RIPPLES;
    }

    if (strcmp(lighting, "single_key") == 0)
    {
        return SINGLE_KEY;
    }

    if (strcmp(lighting, "static") == 0)
    {
        return STATIC;
    }

    return STATIC;
}

void args_init(args_t* args)
{
    if (args == NULL)
    {
        return;
    }

    args->red = 0;
    args->green = 0;
    args->blue = 0;


    args->lighting = STATIC;
    args->speed = 4;
    args->random_colors = 0;
    args->brightness = 4;

    args->vendor_id = -1;
    args->product_id = -1;

    args->verbose = 0;
}

void args_parse(int argc, char** argv, args_t* args)
{
    assert(args != NULL);

    if (argc == 1)
    {
        help_print();
        exit(EXIT_SUCCESS);
    }

    static const char* shortopts = "vl:s:b:rd:";
    static struct option longopts[] = {
        {"red", required_argument, &red, 0},
        {"green", required_argument, &green, 0},
        {"blue", required_argument, &blue, 0},
        {"lighting", required_argument, 0, 'l'},
        {"speed", required_argument, 0, 's'},
        {"brightness", required_argument, 0, 'b'},
        {"random-colors", no_argument, 0, 'r'},
        {"vendor-id", required_argument, &vendor_id, 0},
        {"product-id", required_argument, &product_id, 0},
        {"verbose", no_argument, 0, 'v'},
        {"version", no_argument, &version, 0},
        {0,         0,                 0,  0 }
    };

    int option_index = 0;

    char c;
    while ((c = getopt_long(argc, argv, shortopts, longopts, &option_index)) != -1)
    {
        switch (c)
        {
        case 0:
            if (strcmp(longopts[option_index].name, "red") == 0)
            {
                args->red = atoi(optarg);
                break;
            }

            if (strcmp(longopts[option_index].name, "green") == 0)
            {
                args->green = atoi(optarg);
                break;
            }

            if (strcmp(longopts[option_index].name, "blue") == 0)
            {
                args->blue = atoi(optarg);
                break;
            }

            if (strcmp(longopts[option_index].name, "vendor-id") == 0)
            {
                args->vendor_id = strtol(optarg, NULL, 16);
                break;
            }

            if (strcmp(longopts[option_index].name, "product-id") == 0)
            {
                args->product_id = strtol(optarg, NULL, 16);
                break;
            }

            if (strcmp(longopts[option_index].name, "version") == 0)
            {
                version_print();
                exit(EXIT_SUCCESS);
            }

        case 'v':
            args->verbose = 1;
            break;

        case 'l':
            args->lighting = parse_lighting(optarg);
            break;

        case 's':
            args->speed = atoi(optarg);

            if (args->speed > 4)
            {
                args->speed = 4;
            }

            break;

        case 'b':
            args->brightness = atoi(optarg);

            if (args->brightness > 4)
            {
                args->brightness = 4;
            }

            if (args->brightness <= 0)
            {
                args->brightness = 1;
            }

            break;

        case 'r':
            args->random_colors = true;
            break;

        case '?':
            help_print();
            exit(EXIT_FAILURE);

        }
    }
}
