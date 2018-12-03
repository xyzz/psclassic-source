DESCRIPTION = "mnt-data-ubi"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

APPS_SRC = "${TOPDIR}/../meta/meta-mediatek-aud/recipes-audio/data-ubi-mnt"

inherit workonsrc

WORKONSRC = "${APPS_SRC}"


do_install() {
	install -d ${D}/etc
	install -m 755 ${S}files/data-ubi-mnt.sh ${D}/etc/data-ubi-mnt.sh
}

FILES_${PN}+="etc/data-ubi-mnt.sh"
