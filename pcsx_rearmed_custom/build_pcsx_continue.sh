#!/bin/bash
if [ ! -e config.log ]; then
# run configure
echo "CFLAGS=-march=armv7-a ./configure --sound-drivers=sdl"
CFLAGS=-march=armv7-a ./configure --sound-drivers=sdl
fi
# build.log include stdout & stderr
echo "make -j 4 2>&1 | tee build.log"
make -k -j 4 2>&1 | tee build.log
