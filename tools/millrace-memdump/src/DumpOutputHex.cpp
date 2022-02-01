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

#include <cctype>
#include <iostream>
#include <boost/format.hpp>
#include "DumpOutputHex.h"

DumpOutputHex::DumpOutputHex(uint16_t origin, uint16_t length)
        :DumpOutput(origin, length)
{

}

DumpOutputHex::~DumpOutputHex()
{

}


void DumpOutputHex::do_process(std::ostream &os)
{
    uint16_t length = m_length;

    for (uint16_t i = 0; i < m_length; i += 16)
    {
        os << boost::format("%04x") % (int)(m_origin + i) << ": ";

        uint16_t line_length = (length > 16) ? 16 : length;

        for (uint16_t n = 0; n < 16; n++)
        {
            if (n < line_length)
            {
                os << boost::format("%02x") % (int)(m_buffer[i+n]) << " ";
            }
            else
            {
                os << "   ";
            }
        }

        os << "    ";

        for (uint16_t n = 0; n < line_length; n++)
        {
            os << (char)(isprint(m_buffer[i+n]) ? m_buffer[i+n] : '.');
        }

        os << std::endl;
        length -= 16;
    }
}


