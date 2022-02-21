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



#ifndef Z80UPLOAD_H
#define Z80UPLOAD_H

#include <istream>
#include <vector>
#include "Z80BusExpander.h"

class Z80Upload {
public:
    Z80Upload(uint16_t origin = 0x0000, uint16_t block_size = 0x100);

    virtual ~Z80Upload();

    void process(std::istream &is);

    virtual void do_process(std::istream &is);

protected:
    std::vector<uint8_t> m_buffer;
    uint16_t m_origin;
    uint16_t m_block_size;

private:
    void do_write_mem();
    Z80BusExpander m_z80;
};


#endif //Z80UPLOAD_H
