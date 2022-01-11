/* MIT License

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
SOFTWARE. */

#include "log.h"

static void timestamp(char* into)
{
    if (!into)
        return;

    time_t rawtime;
    struct tm* ti;

    time(&rawtime);
    ti = localtime(&rawtime);

    sprintf(into, "%u-%02u-%02uT%02u:%02u:%02u", 1900 + ti->tm_year, ti->tm_mon + 1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);
}

void log_info(const char* fmt, ...)
{
    if (!fmt)
        return;

    char ts[20];
    timestamp(ts);

    va_list args;
    va_start(args, fmt);

    printf("%s " BLUE "INFO  " END_COLOR, ts);
    vfprintf(stdout, fmt, args);
    printf("\n");

    va_end(args);
}

void log_debug(const char* fmt, ...)
{
    if (!fmt)
        return;

    char ts[20];
    timestamp(ts);

    va_list args;
    va_start(args, fmt);

    printf("%s " YELLOW "DEBUG " END_COLOR, ts);
    vfprintf(stdout, fmt, args);
    printf("\n");

    va_end(args);
}

void log_error(const char* fmt, ...)
{
    if (!fmt)
        return;

    char ts[20];
    timestamp(ts);

    va_list args;
    va_start(args, fmt);

    printf("%s " RED "ERROR " END_COLOR, ts);
    vfprintf(stdout, fmt, args);
    printf("\n");

    va_end(args);
}
