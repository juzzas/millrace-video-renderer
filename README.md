# MillRACE Video application

This is an application to run on the Raspberry PI Zero upon the MillRACE
Video module (designed for RC2014)

#raspi-config

The following raspi-config settings are needed for the application

* enable SPI
* enable OpenGL driver

#Dependencies

The following packages are required:

* cmake
* libsdl2-dev


# Build

To create the build files, cd into `build/` and run `cmake ..` and then
`make`. Then, run the resulting `millrace-video-pi` executable
from the same folder. It will just display a window with a blank white
background until you close the window or hit Cmd+Q (or the equivalent
on your platform).


