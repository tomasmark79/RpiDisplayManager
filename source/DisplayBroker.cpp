#include "displaybroker/DisplayBroker.hpp"

#include <fmt/core.h>
#include <raspi_gpio_hal.h>
#include <stdio.h>
#include <u8g2.h>
#include <wiringPiI2C.h>

DisplayBroker::DisplayBroker() {}

DisplayBroker::~DisplayBroker() {}

// TCA9548A I2C multiplexer channel selector
int DisplayBroker::selectI2CDevice(int fd, int channel)
{
    if (channel < 0 || channel > 7)
    {
        fmt::print(stderr, "Invalid I2C channel: {}\n", channel);
        return 1;
    }

    wiringPiI2CWrite(fd, 1 << channel); // set multiplexer to channel

    return 0;
}
