#!/bin/bash
CONFIG_INSTALL_DIR=./dest
make clean
rm -fr $CONFIG_INSTALL_DIR
rm -f ../../rootfs/usr/sony/lib/charset.*
rm -f ../../rootfs/usr/sony/lib/libcharset.*
rm -f ../../rootfs/usr/sony/lib/libiconv.*
rm -f ../../rootfs/usr/sony/lib/preloadable_libiconv.*
