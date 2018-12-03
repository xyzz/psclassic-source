#!/bin/bash
#
#	@author
#	@brief  generate the top index for each module doc
wait /dev/mtd10
ubiattach /dev/ubi_ctrl -m 10
mount -t ubifs ubi1_0 /data
mount --bind /data/var /var

#create dm-crypt target for userdata and mount
/usr/bin/crypt_target_tool usrdata
if [ $? -eq 0 ]; then
e2fsck -f /dev/mapper/usrdata
resize2fs /dev/mapper/usrdata
mount -t ext4 /dev/mapper/usrdata /data
fi


#create dm-crypt target for gaadata and mount
/usr/bin/crypt_target_tool gaadata
if [ $? -eq 0 ]; then
e2fsck -f /dev/mapper/gaadata
resize2fs /dev/mapper/gaadata
mount -t ext4 /dev/mapper/gaadata /gaadata
fi