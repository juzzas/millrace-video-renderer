//
// Created by justin on 25/01/2022.
//

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

    void write_io_data(uint16_t address, uint8_t data);
    uint8_t read_io_data(uint16_t address);

private:
    void open_spi();
    void close_spi();
    void setup_spi();

    void transfer(const std::vector<uint8_t> &message, std::vector<uint8_t> &response) const;


    std::string m_device_path;
    uint8_t m_bits;
    uint8_t m_mode;
    uint32_t m_speed;
    uint16_t m_delay;
    int m_fd;

    gpiod::chip m_chip;
};


#endif //Z80BUSEXPANDER_H
