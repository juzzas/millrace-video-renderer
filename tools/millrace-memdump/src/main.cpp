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

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "DumpOutputFactory.h"


namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    try {
        // Declare the supported options.
        po::options_description general("General options");
        general.add_options()
                ("help,h", "produce help message")
                ("m_verbose,v", "increase verbosity");

        po::options_description output("Output options");
        output.add_options()
                ("type,y", po::value<std::string>()->value_name("TYPE")->default_value("hex"),
                        "output type (raw, hex, ihex)")
                ("output,o", po::value<std::string>()->value_name("FILE"),
                        "output file name")
                ("address,a", po::value<int>()->value_name("ADDRESS")->default_value(0),
                        "address origin (default: 0x0000)")
                ("length,l", po::value<int>()->value_name("NUM")->default_value(256),
                        "length of memory [bytes] to read (default: 256");

        po::options_description all("Allowed options");
        all.add(general).add(output);

        po::variables_map args;
        po::store(po::command_line_parser(argc, argv).options(all).run(), args);
        po::notify(args);

        if (args.count("help")) {
            std::cout << "Usage: " << argv[0] << " [OPTION]... [FILE]..." << std::endl
                      << std::endl
                      << general << std::endl
                      << output << std::endl;
            return 1;
        }

        std::cout << "length: " << args["length"].as<int>() << std::endl;

        std::shared_ptr<DumpOutput> dump_out = DumpOutputFactory::make_dump_output(
                args["type"].as<std::string>(),
                args["address"].as<int>(),
                args["length"].as<int>()
                );

        if (args.count("output")) {
            std::cout << "Output file: " << args["output"].as<std::string>() << std::endl;
            std::ofstream os;
            os.open(args["output"].as<std::string>());
            dump_out->process(os);
            os.close();
        }
        else
        {
            std::cout << "Output sdtout" << std::endl;
            dump_out->process(std::cout);
        }
    }
    catch (const po::error& ex) {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}


