Summary: ALSA sound library
Name: alsa-lib
Version: 1.1.2
Release: r0
License: LGPLv2.1 & GPLv2+
Group: libs/multimedia
Packager: meta-mediatek-aud
URL: http://www.alsa-project.org
BuildRequires: autoconf-native
BuildRequires: automake-native
BuildRequires: gnu-config-native
BuildRequires: libtool-cross
BuildRequires: libtool-native
BuildRequires: pkgconfig-native
BuildRequires: virtual/arm-poky-linux-gnueabi-compilerlibs
BuildRequires: virtual/arm-poky-linux-gnueabi-gcc
BuildRequires: virtual/libc
Requires: libasound.so.2
Requires: libasound.so.2(ALSA_0.9)
Requires: libasound2 >= 1.1.2
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.4)
Requires: libc6 >= 2.24
Requires: libdl.so.2
Requires: libdl.so.2(GLIBC_2.4)
Requires: libm.so.6
Requires: libpthread.so.0
Requires: librt.so.1
Requires: rtld(GNU_HASH)
Provides: elf(buildid) = 47d86cb898b20889446d8b270f9c636ec65c1f38
Provides: elf(buildid) = e07111c9fc01c9c11368138adb6c8b062fea85cb
Provides: elf(buildid) = 4fdec04c32e334ebc67c4dafea21701772744394
Provides: smixer-ac97.so
Provides: smixer-hda.so
Provides: smixer-sbase.so

%description
ALSA sound library.

%package -n alsa-server
Summary: ALSA sound library
Group: libs/multimedia
Requires: libasound.so.2
Requires: libasound.so.2(ALSA_0.9)
Requires: libasound.so.2(ALSA_0.9.0rc8)
Requires: libasound2 >= 1.1.2
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.4)
Requires: libc6 >= 2.24
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Provides: elf(buildid) = 88b6ed3ce7abfe029861416d73874a17603d914d

%description -n alsa-server
ALSA sound library.

%package -n libasound2
Summary: ALSA sound library
Group: libs/multimedia
Requires: alsa-conf
Requires: alsa-conf-base
Requires: ld-linux-armhf.so.3
Requires: ld-linux-armhf.so.3(GLIBC_2.4)
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.4)
Requires: libc.so.6(GLIBC_2.7)
Requires: libc6 >= 2.24
Requires: libdl.so.2
Requires: libdl.so.2(GLIBC_2.4)
Requires: libm.so.6
Requires: libm.so.6(GLIBC_2.4)
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: librt.so.1
Requires: librt.so.1(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Requires(post): alsa-conf
Requires(post): alsa-conf-base
Requires(post): ld-linux-armhf.so.3
Requires(post): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(post): libc.so.6
Requires(post): libc.so.6(GLIBC_2.4)
Requires(post): libc.so.6(GLIBC_2.7)
Requires(post): libc6 >= 2.24
Requires(post): libdl.so.2
Requires(post): libdl.so.2(GLIBC_2.4)
Requires(post): libm.so.6
Requires(post): libm.so.6(GLIBC_2.4)
Requires(post): libpthread.so.0
Requires(post): libpthread.so.0(GLIBC_2.4)
Requires(post): librt.so.1
Requires(post): librt.so.1(GLIBC_2.4)
Requires(post): rtld(GNU_HASH)
Provides: elf(buildid) = d2f301a2dab1ebd9ad087f0303e601a85170e616
Provides: libasound = 1.1.2
Provides: libasound.so.2
Provides: libasound.so.2(ALSA_0.9)
Provides: libasound.so.2(ALSA_0.9.0)
Provides: libasound.so.2(ALSA_0.9.0rc4)
Provides: libasound.so.2(ALSA_0.9.0rc8)
Provides: libasound.so.2(ALSA_0.9.3)
Provides: libasound.so.2(ALSA_0.9.5)
Provides: libasound.so.2(ALSA_0.9.7)

%description -n libasound2
ALSA sound library.

%package -n alsa-conf-base
Summary: ALSA sound library
Group: libs/multimedia

%description -n alsa-conf-base
ALSA sound library.

%package -n alsa-conf
Summary: ALSA sound library
Group: libs/multimedia

%description -n alsa-conf
ALSA sound library.

%package -n alsa-doc
Summary: ALSA sound library
Group: libs/multimedia

%description -n alsa-doc
ALSA sound library.

%package -n alsa-lib-dbg
Summary: ALSA sound library - Debugging files
Group: devel
Suggests: libasound-dbg
Suggests: libc6-dbg

%description -n alsa-lib-dbg
ALSA sound library.  This package contains ELF symbols and related sources
for debugging purposes.

%package -n alsa-lib-staticdev
Summary: ALSA sound library - Development files (Static Libraries)
Group: devel
Requires: alsa-lib-dev = 1.1.2-r0

%description -n alsa-lib-staticdev
ALSA sound library.  This package contains static libraries for software
development.

%package -n alsa-lib-dev
Summary: ALSA sound library - Development files
Group: devel
Requires: alsa-lib = 1.1.2-r0
Requires: libasound2
Suggests: alsa-conf-base-dev
Suggests: alsa-conf-dev
Suggests: libasound-dev
Suggests: libc6-dev
Provides: alsa-dev
Obsoletes: alsa-dev

%description -n alsa-lib-dev
ALSA sound library.  This package contains symbolic links, header files,
and related items necessary for software development.

%package -n alsa-lib-doc
Summary: ALSA sound library - Documentation files
Group: doc

%description -n alsa-lib-doc
ALSA sound library.  This package contains documentation.

%package -n alsa-lib-locale
Summary: ALSA sound library
Group: libs/multimedia

%description -n alsa-lib-locale
ALSA sound library.

%post -n libasound2
# libasound2 - postinst
#!/bin/sh
if [ x"$D" = "x" ]; then
	if [ -x /sbin/ldconfig ]; then /sbin/ldconfig ; fi
fi


%files
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/lib"
%dir "/usr/lib/alsa-lib"
%dir "/usr/lib/alsa-lib/smixer"
"/usr/lib/alsa-lib/smixer/smixer-sbase.so"
"/usr/lib/alsa-lib/smixer/smixer-hda.so"
"/usr/lib/alsa-lib/smixer/smixer-ac97.so"

%files -n alsa-server
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/bin"
"/usr/bin/aserver"

%files -n libasound2
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/lib"
"/usr/lib/libasound.so.2.0.0"
"/usr/lib/libasound.so.2"

%files -n alsa-conf-base
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/alsa"
%dir "/usr/share/alsa/cards"
%dir "/usr/share/alsa/pcm"
"/usr/share/alsa/alsa.conf"
"/usr/share/alsa/cards/aliases.conf"
"/usr/share/alsa/pcm/dsnoop.conf"
"/usr/share/alsa/pcm/default.conf"
"/usr/share/alsa/pcm/dmix.conf"

%files -n alsa-conf
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/alsa"
%dir "/usr/share/alsa/cards"
%dir "/usr/share/alsa/alsa.conf.d"
%dir "/usr/share/alsa/pcm"
%dir "/usr/share/alsa/ucm"
%dir "/usr/share/alsa/topology"
"/usr/share/alsa/smixer.conf"
"/usr/share/alsa/sndo-mixer.alisp"
%dir "/usr/share/alsa/cards/SI7018"
"/usr/share/alsa/cards/AU8810.conf"
"/usr/share/alsa/cards/Maestro3.conf"
"/usr/share/alsa/cards/TRID4DWAVENX.conf"
"/usr/share/alsa/cards/CMI8738-MC6.conf"
"/usr/share/alsa/cards/VXPocket440.conf"
"/usr/share/alsa/cards/EMU10K1X.conf"
"/usr/share/alsa/cards/PS3.conf"
"/usr/share/alsa/cards/VX222.conf"
"/usr/share/alsa/cards/ENS1370.conf"
"/usr/share/alsa/cards/ENS1371.conf"
"/usr/share/alsa/cards/VIA8233A.conf"
"/usr/share/alsa/cards/ICE1724.conf"
"/usr/share/alsa/cards/PC-Speaker.conf"
"/usr/share/alsa/cards/Audigy2.conf"
"/usr/share/alsa/cards/ICH4.conf"
"/usr/share/alsa/cards/CMI8788.conf"
"/usr/share/alsa/cards/aliases.alisp"
"/usr/share/alsa/cards/GUS.conf"
"/usr/share/alsa/cards/USB-Audio.conf"
"/usr/share/alsa/cards/YMF744.conf"
"/usr/share/alsa/cards/Aureon51.conf"
"/usr/share/alsa/cards/ATIIXP-SPDMA.conf"
"/usr/share/alsa/cards/FWSpeakers.conf"
"/usr/share/alsa/cards/Echo_Echo3G.conf"
"/usr/share/alsa/cards/SB-XFi.conf"
"/usr/share/alsa/cards/RME9636.conf"
"/usr/share/alsa/cards/ICH-MODEM.conf"
"/usr/share/alsa/cards/SI7018.conf"
"/usr/share/alsa/cards/CMI8738-MC8.conf"
"/usr/share/alsa/cards/VIA8233.conf"
"/usr/share/alsa/cards/CMI8338-SWIEC.conf"
"/usr/share/alsa/cards/Loopback.conf"
"/usr/share/alsa/cards/CMI8338.conf"
"/usr/share/alsa/cards/VIA686A.conf"
"/usr/share/alsa/cards/EMU10K1.conf"
"/usr/share/alsa/cards/ICE1712.conf"
"/usr/share/alsa/cards/CA0106.conf"
"/usr/share/alsa/cards/Aureon71.conf"
"/usr/share/alsa/cards/AACI.conf"
"/usr/share/alsa/cards/FM801.conf"
"/usr/share/alsa/cards/CS46xx.conf"
"/usr/share/alsa/cards/HDA-Intel.conf"
"/usr/share/alsa/cards/VIA8237.conf"
"/usr/share/alsa/cards/FireWave.conf"
"/usr/share/alsa/cards/AU8830.conf"
"/usr/share/alsa/cards/PMac.conf"
"/usr/share/alsa/cards/ATIIXP.conf"
"/usr/share/alsa/cards/ICH.conf"
"/usr/share/alsa/cards/Audigy.conf"
"/usr/share/alsa/cards/VXPocket.conf"
"/usr/share/alsa/cards/NFORCE.conf"
"/usr/share/alsa/cards/PMacToonie.conf"
"/usr/share/alsa/cards/RME9652.conf"
"/usr/share/alsa/cards/ES1968.conf"
"/usr/share/alsa/cards/AU8820.conf"
"/usr/share/alsa/cards/ATIIXP-MODEM.conf"
"/usr/share/alsa/cards/SI7018/sndop-mixer.alisp"
"/usr/share/alsa/cards/SI7018/sndoc-mixer.alisp"
"/usr/share/alsa/alsa.conf.d/README"
"/usr/share/alsa/pcm/modem.conf"
"/usr/share/alsa/pcm/hdmi.conf"
"/usr/share/alsa/pcm/front.conf"
"/usr/share/alsa/pcm/rear.conf"
"/usr/share/alsa/pcm/surround71.conf"
"/usr/share/alsa/pcm/surround41.conf"
"/usr/share/alsa/pcm/side.conf"
"/usr/share/alsa/pcm/iec958.conf"
"/usr/share/alsa/pcm/surround50.conf"
"/usr/share/alsa/pcm/surround21.conf"
"/usr/share/alsa/pcm/surround40.conf"
"/usr/share/alsa/pcm/dpl.conf"
"/usr/share/alsa/pcm/center_lfe.conf"
"/usr/share/alsa/pcm/surround51.conf"
%dir "/usr/share/alsa/ucm/DAISY-I2S"
%dir "/usr/share/alsa/ucm/GoogleNyan"
%dir "/usr/share/alsa/ucm/chtrt5645"
%dir "/usr/share/alsa/ucm/tegraalc5632"
%dir "/usr/share/alsa/ucm/PAZ00"
%dir "/usr/share/alsa/ucm/SDP4430"
%dir "/usr/share/alsa/ucm/broadwell-rt286"
%dir "/usr/share/alsa/ucm/PandaBoardES"
%dir "/usr/share/alsa/ucm/PandaBoard"
%dir "/usr/share/alsa/ucm/VEYRON-I2S"
"/usr/share/alsa/ucm/DAISY-I2S/DAISY-I2S.conf"
"/usr/share/alsa/ucm/DAISY-I2S/HiFi.conf"
"/usr/share/alsa/ucm/GoogleNyan/HiFi.conf"
"/usr/share/alsa/ucm/GoogleNyan/GoogleNyan.conf"
"/usr/share/alsa/ucm/chtrt5645/chtrt5645.conf"
"/usr/share/alsa/ucm/chtrt5645/HiFi.conf"
"/usr/share/alsa/ucm/tegraalc5632/tegraalc5632.conf"
"/usr/share/alsa/ucm/PAZ00/HiFi.conf"
"/usr/share/alsa/ucm/PAZ00/PAZ00.conf"
"/usr/share/alsa/ucm/PAZ00/Record.conf"
"/usr/share/alsa/ucm/SDP4430/voice"
"/usr/share/alsa/ucm/SDP4430/record"
"/usr/share/alsa/ucm/SDP4430/voiceCall"
"/usr/share/alsa/ucm/SDP4430/hifi"
"/usr/share/alsa/ucm/SDP4430/FMAnalog"
"/usr/share/alsa/ucm/SDP4430/hifiLP"
"/usr/share/alsa/ucm/SDP4430/SDP4430.conf"
"/usr/share/alsa/ucm/broadwell-rt286/HiFi"
"/usr/share/alsa/ucm/broadwell-rt286/broadwell-rt286.conf"
"/usr/share/alsa/ucm/PandaBoardES/voice"
"/usr/share/alsa/ucm/PandaBoardES/record"
"/usr/share/alsa/ucm/PandaBoardES/PandaBoardES.conf"
"/usr/share/alsa/ucm/PandaBoardES/voiceCall"
"/usr/share/alsa/ucm/PandaBoardES/hifi"
"/usr/share/alsa/ucm/PandaBoardES/FMAnalog"
"/usr/share/alsa/ucm/PandaBoardES/hifiLP"
"/usr/share/alsa/ucm/PandaBoard/voice"
"/usr/share/alsa/ucm/PandaBoard/record"
"/usr/share/alsa/ucm/PandaBoard/PandaBoard.conf"
"/usr/share/alsa/ucm/PandaBoard/voiceCall"
"/usr/share/alsa/ucm/PandaBoard/hifi"
"/usr/share/alsa/ucm/PandaBoard/FMAnalog"
"/usr/share/alsa/ucm/PandaBoard/hifiLP"
"/usr/share/alsa/ucm/VEYRON-I2S/VEYRON-I2S.conf"
"/usr/share/alsa/ucm/VEYRON-I2S/HiFi.conf"
%dir "/usr/share/alsa/topology/broadwell"
%dir "/usr/share/alsa/topology/sklrt286"
"/usr/share/alsa/topology/broadwell/broadwell.conf"
"/usr/share/alsa/topology/sklrt286/codec0_out-cpr-4.bin"
"/usr/share/alsa/topology/sklrt286/codec0_in-mi.bin"
"/usr/share/alsa/topology/sklrt286/media0_in-cpr-0.bin"
"/usr/share/alsa/topology/sklrt286/skl_i2s.conf"
"/usr/share/alsa/topology/sklrt286/codec0_out-mo.bin"
"/usr/share/alsa/topology/sklrt286/codec0_in-cpr-1.bin"
"/usr/share/alsa/topology/sklrt286/hdmi3_pt_out-cpr-11.bin"
"/usr/share/alsa/topology/sklrt286/hdmi2_pt_out-cpr-9.bin"
"/usr/share/alsa/topology/sklrt286/hdmi1_pt_out-cpr-7.bin"
"/usr/share/alsa/topology/sklrt286/codec1_out-cpr-5.bin"
"/usr/share/alsa/topology/sklrt286/hdmi2_pt_out-cpr-10.bin"
"/usr/share/alsa/topology/sklrt286/hdmi3_pt_out-cpr-12.bin"
"/usr/share/alsa/topology/sklrt286/media0_out-cpr-6.bin"
"/usr/share/alsa/topology/sklrt286/codec1_out-mo.bin"
"/usr/share/alsa/topology/sklrt286/hdmi1_pt_out-cpr-8.bin"
"/usr/share/alsa/topology/sklrt286/dmic01_hifi_in-mi.bin"
"/usr/share/alsa/topology/sklrt286/media0_in-mi.bin"
"/usr/share/alsa/topology/sklrt286/dmic01_hifi_in-cpr-3.bin"
"/usr/share/alsa/topology/sklrt286/media0_out-mo.bin"

%files -n alsa-lib-dbg
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/src"
%dir "/usr/lib"
%dir "/usr/bin"
%dir "/usr/src/debug"
%dir "/usr/src/debug/alsa-lib"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/aserver"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/timer"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/alisp"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/hwdep"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/rawmidi"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/ucm"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/input.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/conf.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/socket.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/names.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/output.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/async.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/dlmisc.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/confmisc.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/userfile.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/error.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/shmarea.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/timer/timer.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/timer/timer_query_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/timer/timer_query.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/timer/timer_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/timer/timer_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/tlv.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/setup.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/control_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/ctlparse.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/control_ext.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/namehint.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/control_shm.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/hcontrol.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/cards.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/control_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/control/control.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seq.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seq_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seqmid.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seq_event.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seq_midi_event.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seq_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/seq/seq_old.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/alisp/alisp.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/alisp/alisp_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/alisp/alisp_snd.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/hwdep/hwdep_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/hwdep/hwdep_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/hwdep/hwdep.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/mask_inline.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_copy.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_share.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_meter.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_ext_parm.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_softvol.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/interval.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_params.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_asym.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_empty.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_mmap.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_simple.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_direct.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_rate_linear.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/plugin_ops.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_misc.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_dshare.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_generic.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_shm.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_plug.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/interval.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_iec958.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_dsnoop.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_lfloat.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_plugin.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_mulaw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/mask.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/ladspa.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_multi.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_dmix.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_plugin.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_direct.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_ladspa.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_extplug.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_generic.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_hooks.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_alaw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_rate.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_route.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_ioplug.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_dmix_generic.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_file.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_null.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_adpcm.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/interval_inline.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_mmap_emul.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm_linear.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/pcm/pcm.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/rawmidi/rawmidi_hw.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/rawmidi/rawmidi_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/rawmidi/rawmidi.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/rawmidi/rawmidi_virt.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/ucm/ucm_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/ucm/parser.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/ucm/utils.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/ucm/main.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/mixer_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/simple_abst.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/mixer_simple.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/simple_none.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/bag.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/mixer.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/mixer/simple.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/dapm.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/text.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/builder.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/elem.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/parser.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/tplg_local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/ops.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/channel.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/data.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/pcm.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/src/topology/ctl.c"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer/simple"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer/simple/sbase.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer/simple/sbasedl.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer/simple/hda.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer/simple/ac97.c"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/modules/mixer/simple/sbase.c"
%dir "/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/sound"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/local.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/topology.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/mixer_abst.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/aserver.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/use-case.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/seq.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/mixer.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/error.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/control_external.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/output.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/control.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/conf.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/pcm_rate.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/timer.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/pcm_plugin.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/input.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/seqmid.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/list.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/seq_event.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/pcm.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/hwdep.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/rawmidi.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/global.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/alisp.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/pcm_extplug.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/seq_midi_event.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/pcm_ioplug.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/sound/asequencer.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/sound/asound.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/include/sound/asoc.h"
"/usr/src/debug/alsa-lib/1.1.2-r0/alsa-lib-1.1.2/aserver/aserver.c"
%dir "/usr/lib/alsa-lib"
%dir "/usr/lib/.debug"
%dir "/usr/lib/alsa-lib/smixer"
%dir "/usr/lib/alsa-lib/smixer/.debug"
"/usr/lib/alsa-lib/smixer/.debug/smixer-sbase.so"
"/usr/lib/alsa-lib/smixer/.debug/smixer-hda.so"
"/usr/lib/alsa-lib/smixer/.debug/smixer-ac97.so"
"/usr/lib/.debug/libasound.so.2.0.0"
%dir "/usr/bin/.debug"
"/usr/bin/.debug/aserver"

%files -n alsa-lib-dev
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/lib"
%dir "/usr/include"
%dir "/usr/share/aclocal"
"/usr/share/aclocal/alsa.m4"
%dir "/usr/lib/alsa-lib"
%dir "/usr/lib/pkgconfig"
"/usr/lib/libasound.so"
"/usr/lib/libasound.la"
%dir "/usr/lib/alsa-lib/smixer"
"/usr/lib/alsa-lib/smixer/smixer-hda.la"
"/usr/lib/alsa-lib/smixer/smixer-ac97.la"
"/usr/lib/alsa-lib/smixer/smixer-sbase.la"
"/usr/lib/pkgconfig/alsa.pc"
%dir "/usr/include/alsa"
%dir "/usr/include/sys"
%dir "/usr/include/alsa/sound"
"/usr/include/alsa/topology.h"
"/usr/include/alsa/mixer_abst.h"
"/usr/include/alsa/version.h"
"/usr/include/alsa/use-case.h"
"/usr/include/alsa/seq.h"
"/usr/include/alsa/mixer.h"
"/usr/include/alsa/error.h"
"/usr/include/alsa/control_external.h"
"/usr/include/alsa/output.h"
"/usr/include/alsa/asoundlib.h"
"/usr/include/alsa/pcm_old.h"
"/usr/include/alsa/control.h"
"/usr/include/alsa/conf.h"
"/usr/include/alsa/pcm_rate.h"
"/usr/include/alsa/asoundef.h"
"/usr/include/alsa/timer.h"
"/usr/include/alsa/pcm_plugin.h"
"/usr/include/alsa/pcm_external.h"
"/usr/include/alsa/input.h"
"/usr/include/alsa/seqmid.h"
"/usr/include/alsa/seq_event.h"
"/usr/include/alsa/pcm.h"
"/usr/include/alsa/hwdep.h"
"/usr/include/alsa/rawmidi.h"
"/usr/include/alsa/global.h"
"/usr/include/alsa/alisp.h"
"/usr/include/alsa/pcm_extplug.h"
"/usr/include/alsa/seq_midi_event.h"
"/usr/include/alsa/pcm_ioplug.h"
"/usr/include/alsa/sound/asound_fm.h"
"/usr/include/alsa/sound/sb16_csp.h"
"/usr/include/alsa/sound/sscape_ioctl.h"
"/usr/include/alsa/sound/hdsp.h"
"/usr/include/alsa/sound/tlv.h"
"/usr/include/alsa/sound/hdspm.h"
"/usr/include/alsa/sound/emu10k1.h"
"/usr/include/alsa/sound/type_compat.h"
"/usr/include/alsa/sound/asoc.h"
"/usr/include/sys/asoundlib.h"

