#!/bin/bash

#
# ...because you don't build this often enough
# to remember how.
#

if [ ! -d ./build ];
then
    mkdir build
fi;

cd build
cmake ..
make
