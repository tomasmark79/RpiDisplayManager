#include "displaybroker/DisplayBroker.hpp"

#include <fmt/core.h>
#include <iostream>
#include <stdio.h>


extern "C"
{
#include <u8g2.h>
#include <raspi_gpio_hal.h>
    // #include <wiringPiI2C.h>
    // #include <wiringPi.h>
}

// Multiplexer TCA9548A address
#define TCA9548A_ADDR 0x70

DisplayBroker::DisplayBroker()
{
    std::cout << "DisplayBroker constructor" << std::endl;
    u8g2_t u8g2; // a structure which will contain all the data for one display
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8x8_gpio_and_delay_raspi_gpio_hal);


    // int tca_fd(0);
    // this->selectI2CDevice(tca_fd, TCA9548A_ADDR); // Example I2C address
    // if (tca_fd < 0)
    // {
    //     fprintf(stderr, "Nelze inicializovat TCA9548A!\n");
    //     return;
    // }
}

DisplayBroker::~DisplayBroker() {}

// TCA9548A I2C multiplexer channel selector
int DisplayBroker::selectI2CDevice(int fd, int channel)
{
    if (channel < 0 || channel > 7)
    {
        fmt::print(stderr, "Invalid I2C channel: {}\n", channel);
        return 1;
    }

    // wiringPiI2CWrite(fd, 1 << channel); // set multiplexer to channel

    return 0;
}
