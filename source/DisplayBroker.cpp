#include "displaybroker/DisplayBroker.hpp"

#include <iostream>
#include <stdio.h>

extern "C"
{
#include <bcm2835.h>
#include <raspi_gpio_hal.h>
#include <u8g2.h>
}

// Multiplexer TCA9548A address
#define TCA9548A_ADDR 0x70
#define OLEDS 8

DisplayBroker::DisplayBroker() { this->FourOledScenarioVia_u8g2(); }

DisplayBroker::~DisplayBroker()
{
    bcm2835_i2c_end();
    bcm2835_close();
}

int DisplayBroker::FourOledScenarioVia_u8g2()
{
    u8g2_t *oled = new u8g2_t[OLEDS];
    char buf[32], buf2[32];
    int counter = 0;

    while (true)
    {
        for (int i = 0; i < OLEDS; i++)
        {

            // Switch to channel 0 and initialize the first OLED display
            selectI2CChannel(i);

            if (i == 0 || i == 1)
                u8g2_Setup_ssd1306_i2c_128x64_noname_f(&oled[i], U8G2_R0, u8x8_byte_sw_i2c,
                                                       u8x8_gpio_and_delay_raspi_gpio_hal);
            else
                u8g2_Setup_ssd1306_i2c_128x64_noname_f(&oled[i], U8G2_R2, u8x8_byte_sw_i2c,
                                                       u8x8_gpio_and_delay_raspi_gpio_hal);

            // Set I2C pins - GPIO 3 and 2
            u8x8_SetPin(u8g2_GetU8x8(&oled[i]), U8X8_PIN_I2C_CLOCK, 3);
            u8x8_SetPin(u8g2_GetU8x8(&oled[i]), U8X8_PIN_I2C_DATA, 2);

            sprintf(buf, "Displej %d", i);
            sprintf(buf2, "Counter %d", counter);
            u8g2_InitDisplay(&oled[i]);
            u8g2_SetPowerSave(&oled[i], 0);

            u8g2_ClearBuffer(&oled[i]);

            u8g2_SetFont(&oled[i], u8g2_font_10x20_me);
            u8g2_DrawStr(&oled[i], 0, 30, buf);
            u8g2_DrawStr(&oled[i], 0, 60, buf2);

            //std::cout << "Displaying on OLED " << i << std::endl;
            //std::cout << "Counter: " << counter << std::endl;

            u8g2_SendBuffer(&oled[i]);

            counter++;
        }
    }

    delete[] oled;

    return 0;
}

// TCA9548A
int DisplayBroker::selectI2CChannel(int channel)
{
    if (channel < 0 || channel > 7)
    {
        fprintf(stderr, "Invalid I2C channel: %d\n", channel);
        return 1;
    }

    uint8_t data = 1 << channel;

    if (bcm2835_init() == 0)
    {
        fprintf(stderr, "Error: bcm2835 initialization failed!\n");
        return 1;
    }

    if (bcm2835_i2c_begin() == 0)
    {
        fprintf(stderr, "Error: Cannot start I2C! (Root Access is required)\n");
        bcm2835_close();
        return 1;
    }

    bcm2835_i2c_setSlaveAddress(TCA9548A_ADDR);
    bcm2835_i2c_set_baudrate(100000);

    if (bcm2835_i2c_write((char *)&data, 1) != 0)
    {
        fprintf(stderr, "Cannot set multiplexer to channel %d\n", channel);
        return 1;
    }

    bcm2835_delay(10); // Short delay for stabilization

    return 0;
}
