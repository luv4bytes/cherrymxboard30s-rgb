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

#pragma once

#include "stdlib.h"
#include "libusb-1.0/libusb.h"
#include "math.h"

#include "../log/log.h"
#include "../args/args.h"

#define DEFAULT_VENDOR_ID 0x046a  // Cherry GmbH
#define DEFAULT_PRODUCT_ID 0x0079 // MX Board 3.0 s (Unknown)

/**
 * @brief Sets up libusb.
 *
 * @param args Application arguments.
 */
void device_setup(args_t* args);

/**
 * @brief Searches for the device and sets it to operational state. If no device is found the program exits.
 *
 * @param args Application arguments.
 */
void device_find(args_t* args, struct libusb_device_handle** handle);

/**
 * @brief Sets STATIC lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_static_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets WAVE lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_wave_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets SPECTRUM lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_spectrum_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets BREATHING lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_breathing_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets ROLLING lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_rolling_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets CURVE lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_curve_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets SCAN lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_scan_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets CUSTOM lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_custom_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets RADIATION lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_radiation_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets RIPPLES lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_ripples_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Sets SINGLE KEY lighting.
 *
 * @param lighting Holds information about lighting.
 * @param handle USB device handle.
 */
void device_single_key_light(lighting_t lighting, struct libusb_device_handle* handle);

/**
 * @brief Main function for setting the device lighting.
 *
 * @param args Application arguments.
 * @param handle USB device handle.
 */
void device_set_lighting(args_t* args);

/**
 * @brief Cleans up all resources and releases all interfaces.
 */
void device_cleanup(struct libusb_device_handle* handle);