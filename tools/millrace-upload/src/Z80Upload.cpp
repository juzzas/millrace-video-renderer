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

#include <istream>
#include <iostream>
#include <iterator>
#include "Z80Upload.h"


Z80Upload::Z80Upload(uint16_t origin, uint16_t block_size)
        : m_origin(origin), m_block_size(block_size), m_buffer(block_size)
{
}


Z80Upload::~Z80Upload()
{

}

void Z80Upload::process(std::istream &is)
{
    do_process(is);
    do_write_mem();

}


void Z80Upload::do_process(std::istream &is)
{
    // read data as a block:
//    is.read (reinterpret_cast<char *>(&m_buffer[0]), m_block_size);

    // read the data:
    m_buffer.insert(m_buffer.begin(),
               std::istream_iterator<uint8_t>(is),
               std::istream_iterator<uint8_t>());
}

void Z80Upload::do_write_mem()
{
    m_z80.write_mem_block(m_origin, m_buffer.data(), m_block_size);
}

uint16_t Z80Upload::get_block_size() const
{
    return m_block_size;
}

void Z80Upload::set_block_size(uint16_t block_size)
{
    m_block_size = block_size;
}
