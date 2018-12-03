#!/bin/bash
#
# 使い方:
#         $./build_pcsx.sh
#         →リリース用のpcsxがビルドされます。
#
#         $./build_pcsx.sh enable_menu
#         →Joysticの「select + △」押下でpcsxのメニューが開くpcsxがビルドされます。
#
#
source /usr/local/oecore-x86_64/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi
if [ ! -e config.log ]; then
    # run configure
    # set sdl2-config path
    export PATH=$PATH:$SDKTARGETSYSROOT/usr/bin
    CROSS_COMPILE=arm-poky-linux-gnueabi CFLAGS="-march=armv7ve -mfloat-abi=hard -mfpu=neon-vfpv4 -mcpu=cortex-a7 -mtune=cortex-a7" ./configure --sound-drivers=sdl
fi
# build.log include stdout & stderr
if [ $# -eq 1 ]; then
    if [ $1 = "enable_menu" ]; then
	BUILD_OPTION="CONFIG_ENABLE_MENU=1"
    fi
fi
echo "make $BUILD_OPTION -j4 2>&1 | tee build.log"
make $BUILD_OPTION -j4 2>&1 | tee build.log

TARGET_EXECUTABLE=pcsx
STRIP_OPTION=-s
cp ${TARGET_EXECUTABLE} ${TARGET_EXECUTABLE}.unstripped
$(${STRIP} ${STRIP_OPTION} -o ${TARGET_EXECUTABLE} ${TARGET_EXECUTABLE}.unstripped)

if [ -e ./pcsx ]; then
	mkdir -p ../rootfs/usr/sony/bin/
	cp ./pcsx ../rootfs/usr/sony/bin/
fi
if [ -e ./plugins ]; then
	mkdir -p ../rootfs/usr/sony/bin/plugins
	cp ./plugins/gpu_peops.so ../rootfs/usr/sony/bin/plugins
fi
