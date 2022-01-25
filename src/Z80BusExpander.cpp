//
// Created by justin on 25/01/2022.
//

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdexcept>
#include <sys/ioctl.h>
#include <unistd.h>

#include "Z80BusExpander.h"

const std::string Z80BusExpander::Z80BUS_SPI_DEFAULT_DEVICE = "/dev/spidev0.0";

Z80BusExpander::Z80BusExpander()
        : m_bits(8),
          m_speed(500000)
{
    m_device_path = Z80BusExpander::Z80BUS_SPI_DEFAULT_DEVICE;
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


void Z80BusExpander::write_mem_data(uint16_t address, uint8_t data)
{

}


uint8_t Z80BusExpander::read_mem_data(uint16_t address)
{
    return 0xff;
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

void Z80BusExpander::transfer(const std::vector<uint8_t> &message, std::vector<uint8_t> &response) const
{
    int ret;
    int i;

    response.reserve(message.size());

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)message.data(),
        .rx_buf = (unsigned long)response.data(),
        .len = (unsigned int)message.size(),
        .speed_hz = m_speed,
        .delay_usecs = m_delay,
        .bits_per_word = m_bits,
        };

    for (i = 0; i < message.size(); i++) {
        if (!(i % 16))
            puts("");
        printf("%02X ", message[i]);
    }
    puts("");

    ret = ioctl(m_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
    {
        throw std::runtime_error("can't send spi message");
    }

    for (i = 0; i < message.size(); i++) {
        if (!(i % 16))
            puts("");
        printf("%02X ", response[i]);
    }
    puts("");
}

