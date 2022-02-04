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


#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdexcept>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Z80BusExpander.h"

const std::string Z80BusExpander::Z80BUS_SPI_DEFAULT_DEVICE = "/dev/spidev0.0";
const std::string Z80BusExpander::Z80BUS_CHIP_GPIO_NAME = "gpiochip0";

Z80BusExpander::Z80BusExpander()
        : m_bits(8),
          m_speed(500000)
{
    gpiod::line_request config;

    m_device_path = Z80BusExpander::Z80BUS_SPI_DEFAULT_DEVICE;

    m_chip.open(Z80BUS_CHIP_GPIO_NAME);
    m_pic_busy = m_chip.get_line(23);
    m_pic_data_ready = m_chip.get_line(24);
    m_pic_status_ready = m_chip.get_line(25);

    config.consumer = "z80_expand";
    config.request_type = gpiod::line_request::DIRECTION_INPUT;

    m_pic_busy.request(config);
    m_pic_data_ready.request(config);
    m_pic_status_ready.request(config);

    if (!m_pic_busy.is_requested())
        throw std::runtime_error("unable to request PIC_BUSY line");

    if (!m_pic_data_ready.is_requested())
        throw std::runtime_error("unable to request PIC_DATA_READY line");

    if (!m_pic_status_ready.is_requested())
        throw std::runtime_error("unable to request PIC_STATUS_READY line");

    open_spi();
}


Z80BusExpander::Z80BusExpander(const std::string &device_path)
        : m_device_path(device_path),
          m_bits(8),
          m_speed(500000)
{
    open_spi();
}


Z80BusExpander::~Z80BusExpander()
{
    close_spi();
}

void Z80BusExpander::do_read_mem_block(uint16_t address, uint8_t *buffer, size_t buffer_size)
{

    while (m_pic_busy.get_value() == 1);

    uint8_t set_addr_msb[] = { 0x90, (uint8_t)((address & 0xff00) >> 8) };
    transfer(set_addr_msb, nullptr, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if ((address & 0x00ff) != 0)
    {
        uint8_t set_addr_lsb[] = { 0xA0, (uint8_t)(address & 0xff) };
        transfer(set_addr_lsb, nullptr, 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

#if 1
    uint8_t set_read_command[] = { (uint8_t)(0xB0 | ((buffer_size & 0x0f00) >> 8)), (uint8_t)(buffer_size & 0x00ff) };
    transfer(set_read_command, nullptr, 2);

    while (m_pic_data_ready.get_value() != 1);
    for (int i = 0; i < buffer_size; i++)
    {
        transfer(nullptr, buffer, 1);
        buffer++;
    }

#else
    uint8_t set_read_command[] = { (uint8_t)(0xB0 | ((buffer_size & 0x0f00) >> 8)), (uint8_t)(buffer_size & 0x00ff) };
    transfer(set_read_command, nullptr, 2);

    while (m_pic_data_ready.get_value() != 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    transfer(nullptr, buffer, buffer_size);
#endif


}


void Z80BusExpander::write_mem_data(uint16_t address, uint8_t data)
{
}


uint8_t Z80BusExpander::read_mem_data(uint16_t address)
{
    uint8_t val = 0xff;

    do_read_mem_block(address, &val, 1);

    return val;
}


void Z80BusExpander::read_mem_block(uint16_t address, uint8_t *buffer, size_t buffer_size)
{
    do_read_mem_block(address, buffer, buffer_size);
    //for (auto i = 0; i < buffer_size; i++)
    //    buffer[i] = (uint8_t)(i % 256);

}


void Z80BusExpander::write_io_data(uint16_t address, uint8_t data)
{

}


uint8_t Z80BusExpander::read_io_data(uint16_t address)
{
    return 0xff;
}


void Z80BusExpander::open_spi()
{
    m_fd = open(m_device_path.c_str(), O_RDWR);
    if (m_fd < 0)
    {
        throw std::runtime_error("unable to openSpi device");
    }

    setup_spi();
}


void Z80BusExpander::close_spi()
{
    close(m_fd);
}


void Z80BusExpander::setup_spi()
{
    uint8_t mode = SPI_CONFIG_MODE;
    uint8_t bits = SPI_CONFIG_BITS;
    uint32_t speed = SPI_CONFIG_SPEED;
    uint16_t delay = SPI_CONFIG_DELAY;
    int ret;

    /*
     * spi mode
     */
    ret = ioctl(m_fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1) {
        throw std::runtime_error("can't set spi mode");
    }

    ret = ioctl(m_fd, SPI_IOC_RD_MODE, &m_mode);
    if (ret == -1) {
        throw std::runtime_error("can't get spi mode");
    }

    /*
     * bits per word
     */
    ret = ioctl(m_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1) {
        throw std::runtime_error("can't set bits per word");
    }

    ret = ioctl(m_fd, SPI_IOC_RD_BITS_PER_WORD, &m_bits);
    if (ret == -1) {
        throw std::runtime_error("can't get bits per word");
    }

    /*
     * max speed hz
     */
    ret = ioctl(m_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        throw std::runtime_error("can't set max speed hz");
    }

    ret = ioctl(m_fd, SPI_IOC_RD_MAX_SPEED_HZ, &m_speed);
    if (ret == -1) {
        throw std::runtime_error("can't get max speed hz");
    }
}


void Z80BusExpander::transfer(const uint8_t *message, uint8_t *response, size_t len) const
{
    int ret;
    int i;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)message,
        .rx_buf = (unsigned long)response,
        .len = (unsigned int)len,
        .speed_hz = m_speed,
        .delay_usecs = m_delay,
        .bits_per_word = m_bits,
        };

#if 0
    if (message)
    {
        for (i = 0; i < len; i++) {
            if (!(i % 16))
                puts("");
            printf("%02X ", message[i]);
        }
        puts("");
    }
#endif
    ret = ioctl(m_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
    {
        throw std::runtime_error("can't send spi message");
    }
#if 0
    if (response)
    {
        for (i = 0; i < len; i++) {
            if (!(i % 16))
                puts("");
            printf("%02X ", response[i]);
        }
        puts("");
    }
#endif
}

uint8_t Z80BusExpander::read_status(void)
{
    while (m_pic_busy.get_value() == 1);

    uint8_t set_addr_msb[] = { 0x80, 0x00, 0xff };
    transfer(set_addr_msb, nullptr, 2);

    while (m_pic_data_ready.get_value() == 0);

    uint8_t status_val;
    transfer(nullptr, &status_val, 1);

    return status_val;
}

