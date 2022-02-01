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

#include "DumpOutput.h"


DumpOutput::DumpOutput(uint16_t origin, uint16_t length)
        :m_origin(origin), m_length(length), m_buffer(length)
{
}


DumpOutput::~DumpOutput()
{

}


void DumpOutput::do_process(std::ostream &os)
{
    for (uint8_t i: m_buffer)
        os << i;
}


void DumpOutput::process(std::ostream &os)
{
    do_fetch_mem();
    do_process(os);
}


void DumpOutput::do_fetch_mem()
{
    m_z80.read_mem_block(m_origin, m_buffer.data(), m_length);
}
