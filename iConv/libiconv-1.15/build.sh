#/bin/bash
CONFIG_INSTALL_DIR=./dest
CURRENT_DIR=$(echo $(pwd))
echo "mkdir -p $CURRENT_DIR/$CONFIG_INSTALL_DIR"
mkdir -p $CURRENT_DIR/$CONFIG_INSTALL_DIR
source /usr/local/oecore-x86_64/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi
./configure \
    --enable-shared=yes \
    --host=arm-poky-linux-gnueabi \
    --prefix=$CURRENT_DIR/$CONFIG_INSTALL_DIR \
    --exec-prefix=$CURRENT_DIR/$CONFIG_INSTALL_DIR
make
make install
cp -R $CONFIG_INSTALL_DIR/lib/* ../../rootfs/usr/sony/lib
