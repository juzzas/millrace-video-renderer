// Copyright 2022 Justin Skists <justin.skists@juzza.co.uk>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <string>
#include <vector>
#include <gpiod.hpp>

#ifndef Z80BUSEXPANDER_H
#define Z80BUSEXPANDER_H


class Z80BusExpander
{
public:
    static const std::string Z80BUS_SPI_DEFAULT_DEVICE;
    static const std::string Z80BUS_CHIP_GPIO_NAME;

    const uint8_t SPI_CONFIG_MODE = 0;
    const uint8_t SPI_CONFIG_BITS = 8;
    const uint32_t SPI_CONFIG_SPEED = 500000;
    const uint32_t SPI_CONFIG_DELAY = 0;

    Z80BusExpander();
    explicit Z80BusExpander(const std::string &device_path);

    virtual ~Z80BusExpander();

public:
    void write_mem_data(uint16_t address, uint8_t data);
    uint8_t read_mem_data(uint16_t address);
    void write_mem_block(uint16_t address, uint8_t *buffer, size_t buffer_size);
    void read_mem_block(uint16_t address, uint8_t *buffer, size_t buffer_size);

    void write_io_data(uint16_t address, uint8_t data);
    uint8_t read_io_data(uint16_t address);

    uint8_t read_status(void);

private:
    void open_spi();
    void close_spi();
    void setup_spi();

    void transfer(const uint8_t *message, uint8_t *response, size_t len) const;
    void do_read_mem_block(uint16_t address, uint8_t *buffer, size_t buffer_size);
    void do_write_mem_block(uint16_t address, uint8_t *buffer, size_t buffer_size);


    std::string m_device_path;
    uint8_t m_bits;
    uint8_t m_mode;
    uint32_t m_speed;
    uint16_t m_delay;
    int m_fd;

    gpiod::chip m_chip;
    gpiod::line m_pic_status_ready;
    gpiod::line m_pic_data_ready;
    gpiod::line m_pic_busy;

};


#endif //Z80BUSEXPANDER_H
