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

#include "device.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MSG_LEN 64

/**
 * @brief Defines the type for the functions of releasing and claiming interfaces.
 *
 */
typedef int (*iffunc)(struct libusb_device_handle*, int);

/**
 * @brief Get the device pointer from the current handle.
 *
 * @param handle USB device handle.
 *
 * @return libusb_device* The device pointer.
 */
static struct libusb_device* get_device(struct libusb_device_handle* handle)
{
    assert(handle != NULL);

    libusb_device* dev;
    dev = libusb_get_device(handle);

    if (dev == NULL)
    {
        log_error("%s - Abort.\n", "Error getting device from handle while cleaning up");
        exit(EXIT_FAILURE);
    }

    return dev;
}

/**
 * @brief Get the device descriptor pointer from the given device.
 *
 * @param into Pointer to a libusb_device_descriptor struct.
 * @param dev Device for descriptor.
 */
static void get_device_descriptor(struct libusb_device_descriptor* into, struct libusb_device* dev)
{
    int ret = libusb_get_device_descriptor(dev, into);

    if (ret < LIBUSB_SUCCESS)
    {
        log_error("Error getting device descriptor - %s - Abort.\n", libusb_error_name(ret));
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Applies the given function to all interfaces of a device.
 *
 * @param handle Device handle.
 * @param func The function that shall be applied.
 */
static void perform_on_all_interfaces(struct libusb_device_handle* handle, iffunc func)
{
    struct libusb_device* dev = get_device(handle);
    struct libusb_device_descriptor dev_dsc;

    get_device_descriptor(&dev_dsc, dev);

    struct libusb_config_descriptor* cfg_dsc;
    for (int i = 0; i < dev_dsc.bNumConfigurations; i++)
    {
        int ret = libusb_get_config_descriptor(dev, i, &cfg_dsc);

        if (ret < LIBUSB_SUCCESS)
        {
            log_error("Error getting config descriptor - %s - Abort.\n", libusb_error_name(ret));
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < cfg_dsc->bNumInterfaces; j++)
        {
            int intf_num = cfg_dsc->interface[j].altsetting->bInterfaceNumber;

            ret = func(handle, intf_num);

            if (ret < LIBUSB_SUCCESS)
            {
                log_error("Error releasing interface %i - %s - Abort.\n", intf_num, libusb_error_name(ret));
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * @brief Get the device index from user input.
 *
 * @return int Chosen device index.
 */
static int get_device_index()
{
    int chosen = 0;
    while (1)
    {
        fprintf(stdout, "Please enter device index: ");

        size_t buflen = 6;
        char buf[buflen];
        memset(buf, 0, sizeof(char) * buflen);

        char* in = fgets(buf, buflen, stdin);

        if (in == NULL)
        {
            log_error("Error choosing USB device - Abort.\n");
            exit(EXIT_FAILURE);
        }

        if (!isdigit(buf[0]))
        {
            if (buf[0] == '\n')
            {
                continue;
            }

            char c;
            while ((c = getchar()) == ' ')
            {
            }

            fprintf(stdout, "\n");
            continue;
        }

        chosen = strtol(buf, NULL, 10);
        break;
    }

    return chosen;
}

void device_setup(args_t* args)
{
    int init = libusb_init(NULL);

    if (init < LIBUSB_SUCCESS)
    {
        log_error("%s - Abort.\n", libusb_error_name(init));
        exit(EXIT_FAILURE);
    }

    if (args->verbose == true)
    {
        int set = libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_DEBUG);

        if (set < LIBUSB_SUCCESS)
        {
            log_error("%s - Abort.\n", libusb_error_name(init));
            exit(EXIT_FAILURE);
        }
    }
}

void device_find(args_t* args, struct libusb_device_handle** handleptr)
{
    libusb_device** devices;
    int found = libusb_get_device_list(NULL, &devices);

    if (found < LIBUSB_SUCCESS)
    {
        log_error("Error finding USB devices - %s - Abort.\n", libusb_error_name(found));
        exit(EXIT_FAILURE);
    }

    uint16_t search_vendor = args->vendor_id != -1 ? args->vendor_id : VENDOR_ID;
    uint16_t search_product = args->product_id != -1 ? args->product_id : PRODUCT_ID;

    int ind_i = 0;
    int indizes[found];
    memset(indizes, -1, sizeof(int) * found);

    int chosen = 0;

    // Identify all matching devices that are connected.
    int ret = 0;
    for (int i = 0; i < found; i++)
    {
        libusb_device* dev;
        dev = devices[i];

        struct libusb_device_descriptor dev_dsc = { 0 };
        ret = libusb_get_device_descriptor(dev, &dev_dsc);

        if (ret < LIBUSB_SUCCESS)
        {
            log_error("Error retrieving device descriptor - %s - Abort.\n", libusb_error_name(ret));
            exit(EXIT_FAILURE);
        }

        if (dev_dsc.idVendor == search_vendor && dev_dsc.idProduct == search_product)
        {
            indizes[ind_i++] = i;
        }
    }

    // More than one device
    if (ind_i > 1)
    {
        fprintf(stdout, "More than one matching device found. Please choose the desired device...\n");

        for (int i = 0; i < ARRAY_SIZE(indizes); i++)
        {
            if (indizes[i] == -1)
            {
                break;
            }

            struct libusb_device* dev = devices[indizes[i]];

            struct libusb_device_descriptor dev_dsc = { 0 };
            ret = libusb_get_device_descriptor(dev, &dev_dsc);

            if (ret < LIBUSB_SUCCESS)
            {
                log_error("Error retrieving device descriptor - %s - Abort.\n", libusb_error_name(ret));
                exit(EXIT_FAILURE);
            }

            uint8_t busnum = libusb_get_bus_number(dev);
            uint8_t devaddr = libusb_get_device_address(dev);

            fprintf(stdout, "[%i] Bus: %i, Device: %i\n", indizes[i], busnum, devaddr);
        }

        chosen = get_device_index();
    }
    else
    {
        // If just one device is connected the first index in indizes is taken.
        chosen = indizes[0];
    }

    if (chosen > found - 1)
    {
        log_error("The given index was invalid. Index must not be bigger than %i - Abort.\n", found - 1);
        exit(EXIT_FAILURE);
    }

    ret = libusb_open(devices[chosen], handleptr);

    if (ret < LIBUSB_SUCCESS)
    {
        log_error("Error opening device - %s - Abort.\n", libusb_error_name(ret));
        exit(EXIT_FAILURE);
    }

    libusb_free_device_list(devices, 1);

    if (*handleptr == NULL)
    {
        log_info("%s\n", "No matching device found");
        exit(EXIT_SUCCESS);
    }

    ret = libusb_set_auto_detach_kernel_driver(*handleptr, 1);

    if (ret < LIBUSB_SUCCESS)
    {
        log_error("%s - Abort.\n", libusb_error_name(ret));
        exit(EXIT_FAILURE);
    }

    perform_on_all_interfaces(*handleptr, libusb_claim_interface);
}

void device_static_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x69, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x03,
        lighting.brightness, 0x02, 0x00, 0x00, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting STATIC lighting - %s\n", libusb_error_name(written));
    }
}

void device_wave_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x65 + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x00,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting WAVE lighting - %s\n", libusb_error_name(written));
    }
}

void device_spectrum_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x66 + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x01,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting SPECTRUM lighting - %s\n", libusb_error_name(written));
    }
}

void device_breathing_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x67 + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x02,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting BREATHING lighting - %s\n", libusb_error_name(written));
    }
}

void device_rolling_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x6f + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x0a,
        lighting.brightness, lighting.speed, 0x00, 0x01, 0xff,
        0xff, 0xff, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting ROLLING lighting - %s\n", libusb_error_name(written));
    }
}

void device_curve_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x71 + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x0c,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting CURVE lighting - %s\n", libusb_error_name(written));
    }
}

void device_scan_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    /* TODO: */
}

void device_custom_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    /* TODO: */
}

void device_radiation_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x77 + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x12,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting RADIATION lighting - %s\n", libusb_error_name(written));
    }
}

void device_ripples_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x78 + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x13,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting RIPPLES lighting - %s\n", libusb_error_name(written));
    }
}

void device_single_key_light(lighting_t lighting, struct libusb_device_handle* handle)
{
    uint8_t data[MSG_LEN] = {
        0x04, 0x7a + lighting.speed, 0x03, 0x06, 0x09,
        0x00, 0x00, 0x55, 0x00, 0x15,
        lighting.brightness, lighting.speed, 0x00, lighting.random_colors, lighting.red,
        lighting.green, lighting.blue, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 };

    int written = libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, data, ARRAY_SIZE(data), 0);

    if (written < LIBUSB_SUCCESS)
    {
        log_error("Error setting SINGLE KEY lighting - %s\n", libusb_error_name(written));
    }
}

void device_set_lighting(args_t* args)
{
    assert(args != NULL);

    struct libusb_device_handle* handle = NULL;

    device_setup(args);
    device_find(args, &handle);

    lighting_t lighting;
    lighting_init(&lighting);

    lighting.red = args->red;
    lighting.green = args->green;
    lighting.blue = args->blue;
    lighting.mode = args->lighting;
    lighting.speed = args->speed;
    lighting.brightness = args->brightness;
    lighting.random_colors = args->random_colors;

    switch (lighting.mode)
    {
    case WAVE:
        device_wave_light(lighting, handle);
        break;

    case SPECTRUM:
        device_spectrum_light(lighting, handle);
        break;

    case BREATHING:
        device_breathing_light(lighting, handle);
        break;

    case ROLLING:
        device_rolling_light(lighting, handle);
        break;

    case CURVE:
        device_curve_light(lighting, handle);
        break;

    case SCAN:
        device_scan_light(lighting, handle);
        break;

    case CUSTOM:
        device_custom_light(lighting, handle);
        break;

    case RADIATION:
        device_radiation_light(lighting, handle);
        break;

    case RIPPLES:
        device_ripples_light(lighting, handle);
        break;

    case SINGLE_KEY:
        device_single_key_light(lighting, handle);
        break;

    case STATIC:
        device_static_light(lighting, handle);
        break;
    }

    device_cleanup(handle);
}

void device_cleanup(struct libusb_device_handle* handle)
{
    perform_on_all_interfaces(handle, libusb_release_interface);

    if (handle != NULL)
    {
        libusb_close(handle);
    }

    libusb_exit(NULL);
}