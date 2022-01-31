# Copyright 2022 Justin Skists <justin.skists@juzza.co.uk>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

set(PROJECT_NAME millrace-video-pi)

# http://derekmolloy.ie/hello-world-introductions-to-cmake/

# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

# https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
# Include the FindSDL2.cmake file in order to find SDL2 on all platforms
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

cmake_minimum_required(VERSION 3.15.0)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

# Can manually add sources as follows if desired:
# set(SOURCES src/main.cpp src/anotherfile.cpp)

# set(SDL2_INCLUDE_DIRS /Library/Frameworks/SDL2.framework/Headers)
# set(SDL2_LIBRARIES /Library/Frameworks/SDL2/framework/SDL2)

find_package(Boost REQUIRED COMPONENTS
        program_options system filesystem unit_test_framework)

add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(lib)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/FrameBuffer.cpp
        src/FrameBufferFactory.cpp
        src/FrameBufferTest.cpp
        src/FrameBufferAce.cpp
        src/FrameBufferZ80.cpp)

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        Boost::program_options
        boost
        ${CMAKE_THREAD_LIBS_INIT}
        z80-bus-expander
        )
