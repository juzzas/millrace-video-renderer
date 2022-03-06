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
#include <vector>
#include <filesystem>

#include "Z80UploadFactory.h"

namespace po = boost::program_options;

static int verbose_flag;

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    try {
        // Declare the supported options.
        po::options_description general("General options");
        general.add_options()
                ("help,h", "produce help message")
                ("m_verbose,v", "increase verbosity");

        po::options_description input("Output options");
        input.add_options()
                ("type,t", po::value<std::string>()->value_name("TYPE")->default_value("raw"),
                        "output type (raw, hex, ihex)")
                ("address,a", po::value<int>()->value_name("ADDRESS"),
                        "address origin");

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        po::options_description hidden("Hidden options");
        hidden.add_options()
                ("input-file", po::value< std::vector<std::string> >(), "input file") ;

        po::positional_options_description p;
        p.add("input-file", -1);

        po::options_description all("Allowed options");
        all.add(general).add(input).add(hidden);

        po::variables_map args;
        po::store(po::command_line_parser(argc, argv).options(all).positional(p).run(), args);
        po::notify(args);

        if (args.count("help")) {
            std::cout << "Usage: " << argv[0] << " [OPTION]... [FILE]..." << std::endl
                      << std::endl
                      << general << std::endl
                      << input << std::endl;
            return 1;
        }

        std::shared_ptr<Z80Upload> upload = Z80UploadFactory::makeZ80Upload(
            args["type"].as<std::string>(),
            args["address"].as<int>()
        );

        if (args.count("input-file")) {
            std::vector<std::string> files = args["input-file"].as<std::vector<std::string>>();

            for (const std::string &f : files) {
                uint16_t block_size = std::filesystem::file_size(f);

                std::cout << "Input file: " << f << std::endl;
                std::cout << "length: " << block_size << std::endl;

                upload->set_block_size(block_size);

                std::ifstream ifs;

                ifs.open(f, std::ifstream::in | std::ios::binary);
                ifs.unsetf(std::ios::skipws);

                if (ifs.is_open())
                {
                    upload->process(ifs);
                    ifs.close();
                }
                else
                {
                    std::cerr << "Unable to open file: " << f << std::endl;
                }

            }
        }
        else
        {
            std::cout << "Output stdin" << std::endl;
            upload->process(std::cin);
        }

    }
    catch (const po::error& ex) {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}


