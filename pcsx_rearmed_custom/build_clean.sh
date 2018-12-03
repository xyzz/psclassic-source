#!/bin/bash
# clean make resource
make clean
rm -f plugins/*.so
rm -f build.log
# clean configure resource
rm -f config.log
rm -f config.mak
# clean binary data
if [ -e ../rootfs/usr/sony/bin/pcsx ]; then
	rm -f ../rootfs/usr/sony/bin/pcsx
fi
if [ -e ../rootfs/usr/sony/bin/plugins ]; then
	rm -rf ../rootfs/usr/sony/bin/plugins
fi

TARGET_EXECUTABLE=pcsx
rm -f ${TARGET_EXECUTABLE}.unstripped
