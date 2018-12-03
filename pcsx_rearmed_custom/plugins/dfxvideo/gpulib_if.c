/***************************************************************************
    copyright            : (C) 2001 by Pete Bernert, 2011 notaz

 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version. See also the license.txt file for *
 *   additional informations.                                              *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gpulib/gpu.h"

#define u32 uint32_t

#define INFO_TW        0
#define INFO_DRAWSTART 1
#define INFO_DRAWEND   2
#define INFO_DRAWOFF   3

#define SHADETEXBIT(x) ((x>>24) & 0x1)
#define SEMITRANSBIT(x) ((x>>25) & 0x1)
#define PSXRGB(r,g,b) ((g<<10)|(b<<5)|r)

#define DATAREGISTERMODES unsigned short

#define DR_NORMAL        0
#define DR_VRAMTRANSFER  1

#define GPUSTATUS_READYFORVRAM        0x08000000

// byteswappings

#define SWAP16(x) ({ uint16_t y=(x); (((y)>>8 & 0xff) | ((y)<<8 & 0xff00)); })
#define SWAP32(x) ({ uint32_t y=(x); (((y)>>24 & 0xfful) | ((y)>>8 & 0xff00ul) | ((y)<<8 & 0xff0000ul) | ((y)<<24 & 0xff000000ul)); })

#ifdef __BIG_ENDIAN__

// big endian config
#define HOST2LE32(x) SWAP32(x)
#define HOST2BE32(x) (x)
#define LE2HOST32(x) SWAP32(x)
#define BE2HOST32(x) (x)

#define HOST2LE16(x) SWAP16(x)
#define HOST2BE16(x) (x)
#define LE2HOST16(x) SWAP16(x)
#define BE2HOST16(x) (x)

#else

// little endian config
#define HOST2LE32(x) (x)
#define HOST2BE32(x) SWAP32(x)
#define LE2HOST32(x) (x)
#define BE2HOST32(x) SWAP32(x)

#define HOST2LE16(x) (x)
#define HOST2BE16(x) SWAP16(x)
#define LE2HOST16(x) (x)
#define BE2HOST16(x) SWAP16(x)

#endif

#define GETLEs16(X) ((int16_t)GETLE16((uint16_t *)X))
#define GETLEs32(X) ((int16_t)GETLE32((uint16_t *)X))

#define GETLE16(X) LE2HOST16(*(uint16_t *)X)
#define GETLE32_(X) LE2HOST32(*(uint32_t *)X)
#define GETLE16D(X) ({uint32_t val = GETLE32(X); (val<<16 | val >> 16);})
#define PUTLE16(X, Y) do{*((uint16_t *)X)=HOST2LE16((uint16_t)Y); \
 if(GlobalTextTP!=2 && gpu.vram2) *((uint16_t *)(psxVuw_t + (X - psxVuw)))=HOST2LE16((uint16_t)Y);}while(0)
#define PUTLE32_(X, Y) do{*((uint32_t *)X)=HOST2LE16((uint32_t)Y);}while(0)
#ifdef __arm__
#define GETLE32(X) (*(uint16_t *)(X)|(((uint16_t *)(X))[1]<<16))
#define PUTLE32(X, Y) do{uint16_t *p_=(uint16_t *)(X);uint32_t y_=Y;p_[0]=y_;p_[1]=y_>>16;}while(0)
#else
#define GETLE32 GETLE32_
#define PUTLE32 PUTLE32_
#endif

static const unsigned int SKIP_DATA_MASK[12] = {
 0xffffffff, 0x01ff03ff, 0x00000000, 0x00ffffff,
 0x01ff03ff, 0x01e00000, 0x00ffffff, 0x01ff03ff,
 0x00000000, 0x00ffffff, 0x01ff03ff, 0x00000000
};
#define CMD_DATA_COUNT (123)
static unsigned int skip_frame_data[CMD_DATA_COUNT][12] = {
/*135*/	 0x3c416752, 0x55ff60, 0x3ce0f258, 0x3f644e, 0x55ff6c, 0x90f251, 0x9324f38, 0x8cff5e, 0xd358, 0x8314d36, 0x8aff6b, 0x3e15d351,
/*135*/	 0x3c808080, 0xff77ffe4, 0x3e892795, 0x3c808080, 0xff72ffeb, 0x1052696, 0x3c808080, 0xff75ffed, 0x3c802798, 0x3c808080, 0xff6ffff3, 0x3c802598,
/*136*/	 0x3c416752, 0x56ff62, 0x3ce0f258, 0x3f644e, 0x55ff6e, 0x90f251, 0x8324f38, 0x8dff60,  0xffcad358, 0x8314d36, 0x8aff6d, 0x3c32d351,
/*136*/	0x3c808080, 0xff7affe5, 0x3e89008b, 0x3c808080, 0xff76ffeb, 0x100008f, 0x3c808080, 0xff79ffed, 0x91, 0x3c808080, 0xff72fff3, 0x3e890096,
/*221*/	 0x3c50744d, 0xff56, 0x3cc0513e, 0x3c23371e, 0xffd0ff57, 0x92003e, 0x3c50744d, 0xff69, 0x8385100, 0x3c23371e, 0xffcbff69, 0xc0b0000,
/*222*/	 0x3c50744d, 0xff57, 0x3cc0513e, 0x3c23371e, 0xffd0ff57, 0x92003e, 0x3c50744d, 0xff69, 0x645100, 0x3c23371e, 0xffcbff69, 0xc0b0000,
/*287*/  0x3c808080, 0x0034ffbc, 0x3e189d6b, 0x3c808080, 0x0035ffbc, 0x01059e6b, 0x3c808080, 0x0033ffbb, 0x3e899c6a, 0x3c808080, 0x0035ffbc, 0x01069e6b,
/*287*/  0x3c808080, 0xffe20074, 0x3e89b16e, 0x3c808080, 0xffe20071, 0x0100b267, 0x3c808080, 0xffe10073, 0x0014af6d, 0x3c808080, 0xffe20071, 0xfff7b067,
/*287*/  0x3c406550, 0xffe3ffdb, 0x3d20003f, 0x3c3c5f49, 0xffe5ffef, 0x91002f, 0x3c5d9482, 0x33ffda, 0x103f3f, 0x3c538471, 0x32ffef, 0x103f2f,
/*288*/  0x3c406550, 0xffe4ffdf, 0x3d20003f, 0x3c3c5f49, 0xffe6fff3, 0x91002f, 0x3c5d9482, 0x33ffde, 0x103f3f, 0x3c538471, 0x33fff3, 0x3c3d3f2f,
/*338*/	 0x3c42683d, 0xff8affdd, 0x3e4d00d3, 0x3c6aa86d, 0xff890000, 0x1500b4, 0x3c42683d, 0xff92ffdf, 0x3c723ed3, 0x3c5d9b73, 0xff910007, 0x3c6f3eb4,
/*339*/	 0x3c42683d, 0xff8fffdc, 0x3e4d00d3, 0x3c6aa86d, 0xff8effff, 0x1500b4, 0x3c42683d, 0xff96ffde, 0x3c723ed3, 0x3c5d9b73, 0xff960006, 0x3c6f3eb4,
/*314*/  0x3c42683d, 0xff8cffd9, 0x3e3d00d7, 0x3c42683d, 0xff8bfff7, 0x001500b8, 0x3c42683d, 0xff91ffdb, 0x3c5e3ed7, 0x3c6aa86d, 0xff91fffd, 0x3c6d3eb8,
/*349*/  0x3c42683d, 0xff96004a, 0x3e3d3ed7, 0x3c5d9b73, 0xff930021, 0x00153ef6, 0x3c42683d, 0xff8b004c, 0x3c5100d7, 0x3c6aa86d, 0xff890028, 0x3c6100f6,
/*374*/	 0x3c42683d, 0xff95004a, 0x3e4d3ed3, 0x3c5d9b73, 0xff930021, 0x153ef2, 0x3c42683d, 0xff8a004d, 0x3c5100d3, 0x3c6aa86d, 0xff880028, 0x3c6100f2,
/*375*/	 0x3c42683d, 0xff95004a, 0x3e4d3ed3, 0x3c5d9b73, 0xff930021, 0x153ef2, 0x3c42683d, 0xff8a004d, 0x3c5100d3, 0x3c6aa86d, 0xff890028, 0x3c6100f2,
/*399*/  0x3c456240, 0x100053, 0x3e868e00, 0x3c456240, 0x100070, 0x168e2e, 0x3c324f2d, 0x3b0055, 0x14eddc00, 0x3c324f2d, 0x3c0073, 0x10e8dc2e,
/*400*/  0x3c23371e, 0x110053, 0x3e81a0f4, 0x3c23371e, 0x100053, 0x13a0fa, 0x3c23371e, 0x3c0055, 0xeef4, 0x3c23371e, 0x3c0055, 0xffceeefa,
/*540*/  0x3c577555, 0xffc9009a, 0x3d20001b, 0x25d7d5d, 0xffca00b2, 0x910027, 0x537353, 0xffe5009d, 0xffae0e1b, 0x25a7d5d, 0xffe300b6, 0xffae0d27,
/*541*/  0x3c577555, 0xffc9009a, 0x3d20001b, 0x25d7d5d, 0xffca00b2, 0x910027, 0x537353, 0xffe5009d, 0x3c7f0e1b, 0x25a7d5d, 0xffe300b6, 0x3c800d27,
/*541*/  0x3c808080, 0x1c0010, 0x3e898bac, 0x3c808080, 0x1e0007, 0x1058ea6, 0x3c808080, 0x290016, 0xffa498b1, 0x3c808080, 0x2f000e, 0x3c809fab,
/*79 */  0x3c5a5549, 0xffd1ff76, 0x3bf07fa8, 0x0067645b, 0xffabff6d, 0x00135fa8, 0x006d6a63, 0xffd5ff9b, 0x3c817fc7, 0x0092918c, 0xffacff96, 0x0c195fc7,
/*80 */  0x3c5a5549, 0xffd2ff75, 0x3bf07fa8, 0x0067645b, 0xffabff6c, 0x00135fa8, 0x006d6a63, 0xffd5ff9b, 0x3c647fc7, 0x0092918c, 0xffacff95, 0x0c1c5fc7,
/*81 */  0x3c5a5549, 0xffd3ff74, 0x3bf07fa8, 0x0067645b, 0xffacff6b, 0x00135fa8, 0x006d6a63, 0xffd6ff9a, 0x3c817fc7, 0x0092918c, 0xffadff94, 0x0c195fc7,
/*248*/  0x3c75736e, 0xffabff4f, 0x3bf03fa8, 0x056f6c66, 0xff8fff4f, 0x00132fa8, 0x00969692, 0xffa7ff66, 0x00143fb7, 0x048a8984, 0xff8aff67, 0x003d2fb7,
/*249*/  0x3c6f6c66, 0xff90ff4f, 0x3bf02fa8, 0x0569665e, 0xff74ff51, 0x00131fa8, 0x048a8984, 0xff8aff67, 0x00142fb7, 0x047f7d77, 0xff6dff68, 0x00731fb7,
/*248*/  0x3c808080, 0xff7c0019, 0x3e1600ff, 0x3c808080, 0xff890000, 0x010100ff, 0x3c808080, 0xff7c0016, 0x001300ff, 0x3c808080, 0xff88fffe, 0x088400ff,
/*249*/  0x3c808080, 0xff81001b, 0x3e1600b3, 0x3c808080, 0xff8f0001, 0x010000a0, 0x3c808080, 0xff800018, 0x001300b1, 0x3c808080, 0xff8effff, 0x0884009e,
/*302*/  0x3c745b51, 0xfff3ff5c, 0x3bf03fe7, 0x3c463b31, 0xffceff5d, 0x001300e7, 0x3cffc0b6, 0xfff2ff80, 0x00173fa8, 0x3c785e54, 0xffccff81, 0x3e7a00a8,
/*302*/  0x3c745b51, 0xfff2ff5c, 0x3bf03fe7, 0x3c463b31, 0xffcdff5d, 0x001300e7, 0x3cffc0b6, 0xfff1ff80, 0x00173fa8, 0x3c785e54, 0xffcbff81, 0x001800a8,
/*303*/  0x3c745b51, 0xfff3ff5c, 0x3bf03fe7, 0x3c463b31, 0xffceff5d, 0x001300e7, 0x3cffc0b6, 0xfff3ff80, 0x45453fa8, 0x3c785e54, 0xffccff81, 0x424200a8,
/* 23*/  0x3c808080, 0x015bfff2, 0x3af85009, 0x3c808080, 0x0156ffec, 0x001a4711, 0x3c808080, 0x014cffe8, 0xfff94e00, 0x3c808080, 0x014cffe8, 0xfff24e00,
/* 23*/  0x3c808080, 0x014cffdf, 0x3af84e00, 0x3c808080, 0x0156ffdc, 0x001a4711, 0x3c808080, 0x015cffd8, 0xff8b5009, 0x3c808080, 0x015cffd8, 0xff9c5009,
/* 24*/  0x3c808080, 0x015bfff3, 0x3af8df96, 0x3c808080, 0x0156ffed, 0x0105df91, 0x3c808080, 0x014cffe9, 0x3b77df8e, 0x3c808080, 0x014cffe9, 0x001adf8e,
/* 24*/  0x3c808080, 0x014cffe0, 0x3af8df88, 0x3c808080, 0x0156ffdd, 0x0105df85, 0x3c808080, 0x015cffd9, 0x3b77df82, 0x3c808080, 0x015cffd9, 0x001adf82,
/* 87*/  0x3c808080, 0x0016001a, 0x3af8c682, 0x3c808080, 0x0010001b, 0x0100be82, 0x3c808080, 0x00170014, 0x3c32c686, 0x3c808080, 0x00110015, 0x3c32be85,
/* 87*/  0x3c808080, 0x00190014, 0x3af8df84, 0x3c808080, 0x00170014, 0x0100da84, 0x3c808080, 0x00290018, 0x3c80d685, 0x3c808080, 0x00220019, 0x3c80d384,
/* 88*/  0x3c808080, 0x002c0022, 0x3af895ba, 0x3c808080, 0x0026001e, 0x01058fb7, 0x3c808080, 0x001d001b, 0x005786b5, 0x3c808080, 0x001a001b, 0x0c1c84b5,
/* 88*/  0x3c808080, 0xffdafff2, 0x3bb84198, 0x3c808080, 0xffc9ffe9, 0x01053196, 0x3c808080, 0xffd8fff3, 0x02694099, 0x3c808080, 0xffc7ffea, 0x03852e97,
/* 25*/  0x3c808080, 0xffceffdb, 0x3af582f3, 0x3c808080, 0xffd6ffd5, 0x001d8ff3, 0x3c808080, 0xffc7ffe0, 0xfc0082e9, 0x3c808080, 0xffccffdc, 0xfc0089ea,
/* 25*/  0x3c808080, 0xffb3ffde, 0x3af57eee, 0x3c808080, 0xffb5fff1, 0x001d90f0, 0x3c808080, 0xffb6ffe8, 0xfc008cec, 0x3c808080, 0xffb6ffe8, 0xfc008cec,
/* 26*/  0x3c808080, 0xffcfffda, 0x3af582f3, 0x3c808080, 0xffd6ffd4, 0x001d8ff3, 0x3c808080, 0xffc7ffdf, 0xfc0082e9, 0x3c808080, 0xffccffdb, 0xfc0089ea,
/* 26*/  0x3c808080, 0xffb3ffde, 0x3af57eee, 0x3c808080, 0xffb6fff0, 0x001d90f0, 0x3c808080, 0xffb7ffe7, 0xfc008cec, 0x3c808080, 0xffb7ffe7, 0xfc008cec,
/* 26*/  0x3c808080, 0x015bfff2, 0x3af8df95, 0x3c808080, 0x0155ffec, 0x0105df91, 0x3c808080, 0x014cffe8, 0x3b77df8e, 0x3c808080, 0x014cffe8, 0x001adf8e,
/* 26*/  0x3c808080, 0x014dffde, 0x3af8df87, 0x3c808080, 0x0156ffdc, 0x0105df85, 0x3c808080, 0x015cffd8, 0x3b77df82, 0x3c808080, 0x015cffd8, 0x001adf82,
/* 27*/  0x3c808080, 0xffcfffd9, 0x3af53e84, 0x3c808080, 0xffd7ffd2, 0x0105467f, 0x3c808080, 0xffc8ffdd, 0xfc003788, 0x3c808080, 0xffcdffd9, 0xfc003c85,
/* 27*/  0x3c808080, 0xffb4ffdc, 0x3af52386, 0x3c808080, 0xffb7ffee, 0x01052594, 0x3c808080, 0xffb7ffe6, 0xfc00268e, 0x3c808080, 0xffb7ffe6, 0xfc00268e,
/* 28*/  0x3c808080, 0xffd0ffd7, 0x3af53f83, 0x3c808080, 0xffd8ffd1, 0x0100467f, 0x3c808080, 0xffc8ffdc, 0xfc003787, 0x3c808080, 0xffcdffd8, 0xfc003c84,
/* 28*/  0x3c808080, 0xffb5ffdb, 0x3af52386, 0x3c808080, 0xffb8ffec, 0x01002694, 0x3c808080, 0xffb8ffe4, 0xfc00278d, 0x3c808080, 0xffb8ffe4, 0xfc00278d,
/* 29*/  0x3c808080, 0xffd0ffd6, 0x3af53f82, 0x3c808080, 0xffd8ffcf, 0x0105477d, 0x3c808080, 0xffc9ffdb, 0xfc003885, 0x3c808080, 0xffceffd6, 0xfc003d82,
/* 29*/  0x3c808080, 0xffb5ffda, 0x3af52485, 0x3c808080, 0xffb8ffeb, 0x01052792, 0x3c808080, 0xffb9ffe3, 0xfc00278c, 0x3c808080, 0xffb9ffe3, 0xfc00278c,
/*167*/  0x3c808080, 0x00ab0011, 0x3c3bdf74, 0x3c808080, 0x00a80014, 0x0100df70, 0x3c808080, 0x00b6000f, 0x02bcdf7f, 0x3c808080, 0x00b10013, 0x3c3fdf79,
/*167*/  0x3c808080, 0x00b7001d, 0x3c3bdf6a, 0x3c808080, 0x00b20019, 0x0100df6f, 0x3c808080, 0x00ae001a, 0x01fcdf66, 0x3c808080, 0x00a90018, 0x3c32df69,
/*168*/  0x3c808080, 0x00ac0012, 0x3c3bdf74, 0x3c808080, 0x00a90014, 0x0105df70, 0x3c808080, 0x00b7000f, 0x02dddf7f, 0x3c808080, 0x00b20013, 0x3c40df79,
/*168*/  0x3c808080, 0x00b8001d, 0x3c3bdf6a, 0x3c808080, 0x00b20019, 0x0105df70, 0x3c808080, 0x00ae001a, 0x020edf67, 0x3c808080, 0x00aa0018, 0x3c27df6a,
/*169*/  0x3c808080, 0x00ad0012, 0x3c3bdfad, 0x3c808080, 0x00a90014, 0x0100dfaf, 0x3c808080, 0x00b8000f, 0x02bcdfac, 0x3c808080, 0x00b30013, 0x3c3fdfaf,
/*169*/  0x3c808080, 0x00b9001d, 0x3c3bdfb6, 0x3c808080, 0x00b3001a, 0x0100dfb3, 0x3c808080, 0x00af001a, 0x01fcdfb4, 0x3c808080, 0x00ab0018, 0x3c32dfb2,
/*181*/  0x3c808080, 0x0024fff0, 0x3df928f4, 0x3c808080, 0x0021ffea, 0x007628fc, 0x3c808080, 0x0025ffef, 0x00172bf4, 0x3c808080, 0x0026ffe7, 0xff922bfd,
/*181*/  0x3c808080, 0x000b0001, 0x3db3bbff, 0x3c808080, 0x00060002, 0x0075b9ff, 0x3c808080, 0x0007fffa, 0xffc3bbf7, 0x3c808080, 0x000afffb, 0xffc3bbf7,
/*182*/  0x3c808080, 0x000affec, 0x3db37ba1, 0x3c808080, 0x0005ffef, 0x010076a2, 0x3c808080, 0x0004ffe7, 0x3c80779b, 0x3c808080, 0x0006ffe6, 0x3c807a9c,
/*182*/  0x3c808080, 0x000affec, 0x3dfc7ba1, 0x3c808080, 0x000cffed, 0x01007ca1, 0x3c808080, 0x0005ffef, 0x3c8076a2, 0x3c808080, 0x0007fff1, 0x3c8077a3,
/*151*/  0x3c808080, 0x0011ffe9, 0x3d7c5465, 0x3c808080, 0x0012ffe9, 0x01054c65, 0x3c808080, 0x0012ffe8, 0x00175467, 0x3c808080, 0x0013ffe9, 0x012c4c67,
/*151*/  0x3c808080, 0x0012ffe8, 0x3d7c4ba1, 0x3c808080, 0x0013ffe9, 0x010544a3, 0x3c808080, 0x0012ffe7, 0x3c6e4da1, 0x3c808080, 0x0013ffe8, 0x3c6e44a3,
/*152*/  0x3c808080, 0x0012ffe8, 0x3d7c7e8f, 0x3c808080, 0x0014ffe8, 0x01007f8f, 0x3c808080, 0x0013ffe7, 0xad097f8e, 0x3c808080, 0x0015ffe8, 0xd46a808f,
/*152*/  0x3c808080, 0xffe70002, 0x3d7c5a5b, 0x3c808080, 0xffe80001, 0x01005a5e, 0x3c808080, 0xffe80000, 0x08d95b5e, 0x3c808080, 0xffe80000, 0xc0645b5e,
/*153*/  0x3c808080, 0x0025fffb, 0x3d7ba298, 0x3c808080, 0x0027fff5, 0x0105a493, 0x3c808080, 0x002dfffb, 0x000eab97, 0x3c808080, 0x002cfff6, 0xffe5a994,
/*153*/  0x3c808080, 0xffec0001, 0x3d7c5ca1, 0x3c808080, 0xffecffff, 0x01055c9f, 0x3c808080, 0xffec0000, 0x00175da0, 0x3c808080, 0xffec0000, 0x3c805da0,
/*30 */  0x3c808080, 0x015afff3, 0x3d001939, 0x3c808080, 0x0156ffed, 0x001a1041, 0x3c808080, 0x014bffe9, 0xffdc1730, 0x3c808080, 0x014bffe9, 0x00121730,
/*30 */  0x3c808080, 0x014bffe0, 0x3d001730, 0x3c808080, 0x0156ffdd, 0x001a1041, 0x3c808080, 0x015cffd9, 0xff931939, 0x3c808080, 0x015cffd9, 0xffbb1939,
/*31 */  0x3c808080, 0x015bfff2, 0x3d001939, 0x3c808080, 0x0156ffec, 0x001a1041, 0x3c808080, 0x014cffe8, 0x3d1b1730, 0x3c808080, 0x014cffe8, 0x00161730,
/*31 */  0x3c808080, 0x014cffdf, 0x3d001730, 0x3c808080, 0x0156ffdc, 0x001a1041, 0x3c808080, 0x015cffd8, 0x3d1b1939, 0x3c808080, 0x015cffd8, 0x00161939,
/*32 */  0x3c808080, 0x015bfff3, 0x3d001939, 0x3c808080, 0x0156ffed, 0x001a1041, 0x3c808080, 0x014cffe9, 0xffdc1730, 0x3c808080, 0x014cffe9, 0x00121730,
/*32 */  0x3c808080, 0x014cffe0, 0x3d001730, 0x3c808080, 0x0157ffdd, 0x001a1041, 0x3c808080, 0x015cffd9, 0xff931939, 0x3c808080, 0x015cffd9, 0xffbb1939,
/*33 */  0x3c808080, 0x015afff2, 0x3d00df96, 0x3c808080, 0x0155ffed, 0x0100df91, 0x3c808080, 0x014bffe9, 0x3d1bdf8e, 0x3c808080, 0x014bffe9, 0x0016df8e,
/*33 */  0x3c808080, 0x014cffdf, 0x3d00df88, 0x3c808080, 0x0156ffdd, 0x0100df85, 0x3c808080, 0x015cffd9, 0x3d1bdf82, 0x3c808080, 0x015cffd9, 0x0016df82,
/*34 */  0x3c808080, 0x015dfff2, 0x3d00df96, 0x3c808080, 0x0156ffec, 0x0105df91, 0x3c808080, 0x014effe9, 0xffdcdf8e, 0x3c808080, 0x014effe9, 0x0012df8e,
/*34 */  0x3c808080, 0x014fffdf, 0x3d00df88, 0x3c808080, 0x0158ffdc, 0x0105df85, 0x3c808080, 0x015effd8, 0xff93df82, 0x3c808080, 0x015effd8, 0xffbbdf82,
/*35 */  0x3c808080, 0x015efff3, 0x3d00df95, 0x3c808080, 0x0157ffed, 0x0100df91, 0x3c808080, 0x014fffe9, 0x3d1bdf8e, 0x3c808080, 0x014fffe9, 0x0016df8e,
/*35 */  0x3c808080, 0x0150ffe0, 0x3d00df86, 0x3c808080, 0x0158ffdd, 0x0100df85, 0x3c808080, 0x015fffd9, 0x3d1bdf82, 0x3c808080, 0x015fffd9, 0x0016df82,
/*36 */  0x3c808080, 0x006d001c, 0x3d4fdfb9, 0x3c808080, 0x00670009, 0x0105dfac, 0x3c808080, 0x006c0020, 0xffe4dfbc, 0x3c808080, 0x0065000c, 0xffe4dfaf,
/*36 */  0x3c808080, 0x0075001f, 0x3d4fdfbb, 0x3c808080, 0x006e000c, 0x0105dfae, 0x3c808080, 0x006d001c, 0xffe2dfb9, 0x3c808080, 0x00670009, 0xffe2dfac,
/*111*/  0x3c808080, 0x0018001b, 0x3d00c682, 0x3c808080, 0x0012001c, 0x0100be82, 0x3c808080, 0x00190015, 0x0035c686, 0x3c808080, 0x00130016, 0x0032be85,
/*111*/  0x3c808080, 0x001b0015, 0x3d00df82, 0x3c808080, 0x00190015, 0x0100df82, 0x3c808080, 0x002b0019, 0x005ddd83, 0x3c808080, 0x00240019, 0x014cdb82,
/*112*/  0x3c808080, 0x002f0022, 0x3d0095ba, 0x3c808080, 0x0028001e, 0x01058fb7, 0x3c808080, 0x0020001b, 0xffe786b5, 0x3c808080, 0x001d001b, 0xffab84b5,
/*112*/  0x3c808080, 0x0028001e, 0x3d008fb7, 0x3c808080, 0x0021001d, 0x010587b6, 0x3c808080, 0x001d001b, 0x003084b5, 0x3c808080, 0x0018001c, 0x00007eb5,
/*113*/  0x3c808080, 0x0033001f, 0x3d0093b7, 0x3c808080, 0x002c001d, 0x01008cb6, 0x3c808080, 0x0028001c, 0xffcf88b5, 0x3c808080, 0x0021001d, 0xffda82b5,
/*113*/  0x3c808080, 0x00340019, 0x3d0094b3, 0x3c808080, 0x00290015, 0x010089b0, 0x3c808080, 0x002c0019, 0x01328cb3, 0x3c808080, 0x00220016, 0x043283b1,
/*191*/  0x3c808080, 0x00670014, 0x3de2c2bb, 0x3c808080, 0x00630014, 0x0100b0b9, 0x3c808080, 0x0072001e, 0x0019d7c8, 0x3c808080, 0x0072001e, 0x3cd1d7c8,
/*191*/  0x3c808080, 0x00630014, 0x3de2b0b9, 0x3c808080, 0x005f0014, 0x0100a1bb, 0x3c808080, 0x0067001d, 0x0019b4c9, 0x3c808080, 0x0064001c, 0x3c8da9c7,
/*192*/  0x3c808080, 0x0063001d, 0x3de2dfcb, 0x3c808080, 0x005c001a, 0x0105dfc8, 0x3c808080, 0x0066001f, 0x001adfce, 0x3c808080, 0x0060001a, 0x3c84dfc9,
/*192*/  0x3c808080, 0x00680014, 0x3de2d8af, 0x3c808080, 0x00630013, 0x0105d3af, 0x3c808080, 0x0073001e, 0x0019dfb7, 0x3c808080, 0x0073001e, 0x3cd1dfb7,
/*40 */  0x3c808080, 0xffcfffda, 0x3ce582f3, 0x3c808080, 0xffd6ffd4, 0x001d8ff3, 0x3c808080, 0xffc7ffdf, 0xfc0082e9, 0x3c808080, 0xffccffdb, 0xfc0089ea,
/*41 */  0x3c808080, 0xffcfffd9, 0x3ce53d85, 0x3c808080, 0xffd7ffd2, 0x01054580, 0x3c808080, 0xffc8ffdd, 0xfc003688, 0x3c808080, 0xffcdffd9, 0xfc003b85,
/*41 */  0x3c808080, 0xffb4ffdc, 0x3ce52287, 0x3c808080, 0xffb7ffee, 0x01052595, 0x3c808080, 0xffb7ffe6, 0xfc00268e, 0x3c808080, 0xffb7ffe6, 0xfc00268e,
/*40 */  0x3c808080, 0xffb3ffde, 0x3ce57eee, 0x3c808080, 0xffb6fff0, 0x001d90f0, 0x3c808080, 0xffb7ffe7, 0xfc008cec, 0x3c808080, 0xffb7ffe7, 0xfc008cec,
/*42 */  0x3c808080, 0xffd0ffd7, 0x3ce53f83, 0x3c808080, 0xffd8ffd1, 0x0100467f, 0x3c808080, 0xffc8ffdc, 0xfc003787, 0x3c808080, 0xffcdffd8, 0xfc003c84,
/*42 */  0x3c808080, 0xffb5ffdb, 0x3ce52386, 0x3c808080, 0xffb8ffec, 0x01002694, 0x3c808080, 0xffb8ffe4, 0xfc00278d, 0x3c808080, 0xffb8ffe4, 0xfc00278d,
/*43 */  0x3c808080, 0xffd0ffd6, 0x3ce53f82, 0x3c808080, 0xffd8ffcf, 0x0105477d, 0x3c808080, 0xffc9ffdb, 0xfc003885, 0x3c808080, 0xffceffd6, 0xfc003d82,
/*43 */  0x3c808080, 0xffb5ffda, 0x3ce52485, 0x3c808080, 0xffb8ffeb, 0x01052792, 0x3c808080, 0xffb9ffe3, 0xfc00278c, 0x3c808080, 0xffb9ffe3, 0xfc00278c,
/*276*/  0x3c808080, 0x00ac0012, 0x3d83df74, 0x3c808080, 0x00a90014, 0x0105df70, 0x3c808080, 0x00b7000f, 0x02bcdf7f, 0x3c808080, 0x00b20013, 0x3c3fdf79,
/*276*/  0x3c808080, 0x00b8001d, 0x3d83df6a, 0x3c808080, 0x00b20019, 0x0105df70, 0x3c808080, 0x00ae001a, 0x01fcdf67, 0x3c808080, 0x00aa0018, 0x3c27df6a,
/*277*/  0x3c808080, 0x00ae0012, 0x3d83dfad, 0x3c808080, 0x00aa0014, 0x0100dfaf, 0x3c808080, 0x00b9000f, 0x02dddfac, 0x3c808080, 0x00b30013, 0x3c40dfaf,
/*277*/  0x3c808080, 0x00ba001d, 0x3d83dfb6, 0x3c808080, 0x00b4001a, 0x0100dfb3, 0x3c808080, 0x00b0001a, 0x020edfb4, 0x3c808080, 0x00ac0018, 0x3c32dfb2,
/*253*/  0x3c191e0a, 0x009600df, 0x38b18ffb, 0x3c242a14, 0x009300d2, 0x000c92fb, 0x3c779173, 0x007e00d3, 0x00958ff0, 0x3c748c6e, 0x008000c8, 0x009493f0,
/*254*/  0x3c191e0a, 0x00bb00ee, 0x38b193fb, 0x3c4b5e48, 0x00a400dc, 0x000c94f0, 0x3c191e0a, 0x00b900ed, 0x001792fb, 0x3c687c5f, 0x00a300da, 0x0c1c93f0,
/*255*/  0x3c33432f, 0x00cd0109, 0x38b18ffb, 0x3c191e0a, 0x00cc00fa, 0x000c92fb, 0x3c738a6c, 0x00af00ec, 0x00958ff0, 0x3c627457, 0x00b400e2, 0x009493f0,
/*266*/  0x3c1a200c, 0x00a700ed, 0x38b18ffb, 0x3c1e240f, 0x00a500de, 0x000c92fb, 0x3c779072, 0x008d00db, 0x00178ff0, 0x3c6e8567, 0x009000d0, 0x0c1c93f0,
/*73 */  0x3c808080, 0xffdbfff4, 0x3d3c4e56, 0x3c808080, 0xffdefff4, 0x01054e55, 0x3c808080, 0xffd5fff0, 0x3c994459, 0x3c808080, 0xffd5fff0, 0x3c954459,
/*73 */  0x3c808080, 0xffd5fff0, 0x3d3c4459, 0x3c808080, 0xffd5fff2, 0x01054d58, 0x3c808080, 0xffdbfff4, 0x3ccb4e56, 0x3c808080, 0xffdbfff4, 0x3cdc4e56,
/*74 */  0x3c808080, 0xffddfff3, 0x3d3c465a, 0x3c808080, 0xffdffff7, 0x01004555, 0x3c808080, 0xffdffff2, 0x7742405a, 0x3c808080, 0xffdffff2, 0xc87d405a,
/*74 */  0x3c808080, 0xffde0000, 0x3d3c5dac, 0x3c808080, 0xffe30001, 0x01005fac, 0x3c808080, 0xffe0fffc, 0xde585dac, 0x3c808080, 0xffe5fffe, 0x028160ac,
/*75 */  0x3c808080, 0xfff0fff7, 0x3d7c549b, 0x3c808080, 0xffeefff5, 0x0105519a, 0x3c808080, 0xffeffff7, 0x3c68539c, 0x3c808080, 0xffeffff7, 0x3c7e539c,
/*75 */  0x3c808080, 0xffe7fff1, 0x3d3c4b97, 0x3c808080, 0xffeafff1, 0x01054e97, 0x3c808080, 0xffe2ffed, 0x3c994594, 0x3c808080, 0xffe2ffed, 0x3c954594,
/*76 */  0x3c808080, 0xfff3fff5, 0x3d7c5a9a, 0x3c808080, 0xfff1fff3, 0x01005899, 0x3c808080, 0xfff2fff5, 0x5c4d5a9a, 0x3c808080, 0xfff2fff5, 0x0de15a9a,
/*76 */  0x3c808080, 0xffeaffef, 0x3d3c5195, 0x3c808080, 0xffedffef, 0x01005496, 0x3c808080, 0xffe5ffeb, 0x0b2f4c93, 0x3c808080, 0xffe5ffeb, 0xc9694c93,
/*30 */  0x3c808080, 0x0027000e, 0x3d73a588, 0x3c808080, 0x0024000e, 0x0100a288, 0x3c808080, 0x00270012, 0x9f92a48b, 0x3c808080, 0x00240012, 0x5e72a28b,
/*30 */  0x3c808080, 0x0021000e, 0x3d7ba088, 0x3c808080, 0x0026000f, 0x0100a189, 0x3c808080, 0x001b000b, 0x3a3ea68a, 0x3c808080, 0x0021000c, 0xda49a88a,
/*31 */  0x3c808080, 0x000c0011, 0x3d7b978b, 0x3c808080, 0x0009000d, 0x0105968a, 0x3c808080, 0x000e0011, 0x00f9998b, 0x3c808080, 0x000c000d, 0x3c50988a,
/*31 */  0x3c808080, 0x0020000f, 0x3d7ba288, 0x3c808080, 0x00260010, 0x0105a389, 0x3c808080, 0x001c000c, 0x01d9a88a, 0x3c808080, 0x0022000d, 0x3c93aa8a,
/*32 */  0x3c808080, 0x0024000e, 0x3d7391a9, 0x3c808080, 0x0021000f, 0x01008eab, 0x3c808080, 0x0025000f, 0x829494ab, 0x3c808080, 0x00210010, 0xbf7790ac,
/*32 */  0x3c808080, 0x00240013, 0x3d7391ae, 0x3c808080, 0x00250013, 0x010094ae, 0x3c808080, 0x00210012, 0x24868eac, 0x3c808080, 0x00210011, 0x312390ac,
/*33 */  0x3c808080, 0x0009000d, 0x3d7b79aa, 0x3c808080, 0x00090009, 0x010578a7, 0x3c808080, 0x000d000d, 0x00f97caa, 0x3c808080, 0x000d0009, 0x3c707ca7,
/*33 */  0x3c808080, 0x00060002, 0x3d7b80a6, 0x3c808080, 0xffff0002, 0x01057aa5, 0x3c808080, 0x0005fffb, 0x03ff80a1, 0x3c808080, 0x0000fffb, 0x3c807ba0,
};
#define PMT_CMD_COUNT (12)
#define PMT_CMD_SIZE (8)
#define PMT_CMD_ex_SIZE (1)
#define PMT_CMD_60_SIZE (3)
#define PMT_CMD_64_SIZE (4)

const unsigned int PMT_MASK_60_62[PMT_CMD_60_SIZE] = {
  0xffffffff, 0x001fffff, 0x01ff03ff
};
static const unsigned int PMT_MASK_64[PMT_CMD_64_SIZE] = {
  0xffffffff, 0x00ffffff, 0xffffffff, 0x01ff03ff
};
static const unsigned int PMT_MASK_38[PMT_CMD_SIZE] = {
  0xffffffff, 0x001fffff, 0x00ffffff, 0, 0x00ffffff, 0x001fffff, 0x00ffffff, 0
};
/* PMT life label */
static unsigned int* PMT_MASK[PMT_CMD_COUNT] = {
 PMT_MASK_60_62,
 PMT_MASK_60_62,
 PMT_MASK_60_62,
 PMT_MASK_60_62,
 PMT_MASK_60_62,
 PMT_MASK_38,
 PMT_MASK_60_62,
 PMT_MASK_64,
 PMT_MASK_64,
 PMT_MASK_64,
 PMT_MASK_64,
 PMT_MASK_64
};
static  const unsigned int PMT_CMD[PMT_CMD_COUNT][PMT_CMD_SIZE+1] = {
 /* 35, cmd 60,len 3 */ 3, 0x60000000, 0x00280048, 0x00060001, 0, 0, 0, 0, 0,
 /* 35, cmd 60,len 3 */ 3, 0x60000000, 0x002d0010, 0x00010038, 0, 0, 0, 0, 0,
 /* 35, cmd 60,len 3 */ 3, 0x60000000, 0x00280010, 0x00010038, 0, 0, 0, 0, 0,
 /* 35, cmd 60,len 3 */ 3, 0x60000000, 0x0028000f, 0x00060001, 0, 0, 0, 0, 0,
 /* 35, cmd 62,len 3 */ 3, 0x62181800, 0x00290010, 0x00040038, 0, 0, 0, 0, 0,
 /* 35, cmd 38,len 8 */ 8, 0x385fbf1f, 0x00290010, 0x005fbf1f, 0x00290027, 0x005fbf1f, 0x002d0010, 0x645fbf1f, 0x002d0027,
 /* 35, cmd 62,len 3 */ 3, 0x62000000, 0x002b0013, 0x00070020, 0, 0, 0, 0, 0,
 /* 35, cmd 64,len 4 */ 4, 0x64ffffff, 0x002c002c, 0x7ffced42, 0x00050006, 0, 0, 0, 0,
 /* 35, cmd 64,len 4 */ 4, 0x64ffffff, 0x002c0026, 0x7ffced90, 0x00050006, 0, 0, 0, 0,
 /* 35, cmd 64,len 4 */ 4, 0x64ffffff, 0x002c0020, 0x7ffced66, 0x00050006, 0, 0, 0, 0,
 /* 35, cmd 64,len 4 */ 4, 0x64ffffff, 0x002c001a, 0x7ffced18, 0x00050006, 0, 0, 0, 0,
 /* 35, cmd 64,len 4 */ 4, 0x64ffffff, 0x002c0014, 0x7ffced48, 0x00050006, 0, 0, 0, 0
};
extern int g_gpu_patch_flag;
/////////////////////////////////////////////////////////////////////////////

typedef struct VRAMLOADTTAG
{
 short x;
 short y;
 short Width;
 short Height;
 short RowsRemaining;
 short ColsRemaining;
 unsigned short *ImagePtr;
} VRAMLoad_t;

/////////////////////////////////////////////////////////////////////////////

typedef struct PSXPOINTTAG
{
 int32_t x;
 int32_t y;
} PSXPoint_t;

typedef struct PSXSPOINTTAG
{
 short x;
 short y;
} PSXSPoint_t;

typedef struct PSXRECTTAG
{
 short x0;
 short x1;
 short y0;
 short y1;
} PSXRect_t;

// linux defines for some windows stuff

#define FALSE 0
#define TRUE 1
#define BOOL unsigned short
#define LOWORD(l)           ((unsigned short)(l))
#define HIWORD(l)           ((unsigned short)(((uint32_t)(l) >> 16) & 0xFFFF))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define DWORD uint32_t
#ifndef __int64
#define __int64 long long int
#endif

typedef struct RECTTAG
{
 int left;
 int top;
 int right;
 int bottom;
}RECT;

/////////////////////////////////////////////////////////////////////////////

typedef struct TWINTAG
{
 PSXRect_t  Position;
 int xmask, ymask;
} TWin_t;

/////////////////////////////////////////////////////////////////////////////

typedef struct PSXDISPLAYTAG
{
 PSXPoint_t  DisplayModeNew;
 PSXPoint_t  DisplayMode;
 PSXPoint_t  DisplayPosition;
 PSXPoint_t  DisplayEnd;

 int32_t        Double;
 int32_t        Height;
 int32_t        PAL;
 int32_t        InterlacedNew;
 int32_t        Interlaced;
 int32_t        RGB24New;
 int32_t        RGB24;
 PSXSPoint_t DrawOffset;
 int32_t        Disabled;
 PSXRect_t   Range;

} PSXDisplay_t;

/////////////////////////////////////////////////////////////////////////////

// draw.c

extern int32_t           GlobalTextAddrX,GlobalTextAddrY,GlobalTextTP;
extern int32_t           GlobalTextABR,GlobalTextPAGE;
extern short          ly0,lx0,ly1,lx1,ly2,lx2,ly3,lx3;
extern long           lLowerpart;
extern BOOL           bCheckMask;
extern unsigned short sSetMask;
extern unsigned long  lSetMask;
extern short          g_m1;
extern short          g_m2;
extern short          g_m3;
extern short          DrawSemiTrans;

// prim.c

extern BOOL           bUsingTWin;
extern TWin_t         TWin;
extern void (*primTableJ[256])(unsigned char *);
extern void (*primTableSkip[256])(unsigned char *);
extern unsigned short  usMirror;
extern int            iDither;
extern uint32_t  dwCfgFixes;
extern uint32_t  dwActFixes;
extern int            iUseFixes;
extern int            iUseDither;
extern int            isToShinDen;
extern int            isBiosLogoEnd;
extern int            *scenes;
extern int            regions;
extern int            iTrimJaggyFrame;
extern BOOL           bDoVSyncUpdate;
extern int32_t           drawX;
extern int32_t           drawY;
extern int32_t           drawW;
extern int32_t           drawH;

// gpu.h

#define OPAQUEON   10
#define OPAQUEOFF  11

#define KEY_RESETTEXSTORE 1
#define KEY_SHOWFPS       2
#define KEY_RESETOPAQUE   4
#define KEY_RESETDITHER   8
#define KEY_RESETFILTER   16
#define KEY_RESETADVBLEND 32
#define KEY_BADTEXTURES   128
#define KEY_CHECKTHISOUT  256

#if !defined(__BIG_ENDIAN__) || defined(__x86_64__) || defined(__i386__)
#ifndef __LITTLE_ENDIAN__
#define __LITTLE_ENDIAN__
#endif
#endif

#ifdef __LITTLE_ENDIAN__
#define RED(x) (x & 0xff)
#define BLUE(x) ((x>>16) & 0xff)
#define GREEN(x) ((x>>8) & 0xff)
#define COLOR(x) (x & 0xffffff)
#elif defined __BIG_ENDIAN__
#define RED(x) ((x>>24) & 0xff)
#define BLUE(x) ((x>>8) & 0xff)
#define GREEN(x) ((x>>16) & 0xff)
#define COLOR(x) SWAP32(x & 0xffffff)
#endif

PSXDisplay_t      PSXDisplay;
unsigned char  *psxVub;
signed   char  *psxVsb;
unsigned short *psxVuw;
unsigned short *psxVuw_t;
unsigned short *psxVuw_eom;
signed   short *psxVsw;
uint32_t *psxVul;
int32_t  *psxVsl;

long              lGPUstatusRet;
uint32_t          lGPUInfoVals[16];

VRAMLoad_t        VRAMWrite;
VRAMLoad_t        VRAMRead;

DATAREGISTERMODES DataWriteMode;
DATAREGISTERMODES DataReadMode;

BOOL           bCheckMask = FALSE;
unsigned short sSetMask = 0;
unsigned long  lSetMask = 0;
long           lLowerpart;

#include "soft.c"
#include "prim.c"

/////////////////////////////////////////////////////////////////////////////

static void set_vram(void *vram)
{
 psxVub=vram;

 psxVsb=(signed char *)psxVub;                         // different ways of accessing PSX VRAM
 psxVsw=(signed short *)psxVub;
 psxVsl=(int32_t *)psxVub;
 psxVuw=(unsigned short *)psxVub;
 psxVul=(uint32_t *)psxVub;

 psxVuw_eom=psxVuw+1024*512;                           // pre-calc of end of vram
 if (gpu.vram2)
   psxVuw_t = gpu.vram2;
 else
   psxVuw_t = psxVuw;
}

int renderer_init(void)
{
 set_vram(gpu.vram);

 PSXDisplay.RGB24        = FALSE;                      // init some stuff
 PSXDisplay.Interlaced   = FALSE;
 PSXDisplay.DrawOffset.x = 0;
 PSXDisplay.DrawOffset.y = 0;
 PSXDisplay.DisplayMode.x= 320;
 PSXDisplay.DisplayMode.y= 240;
 PSXDisplay.Disabled     = FALSE;
 PSXDisplay.Range.x0=0;
 PSXDisplay.Range.x1=0;
 PSXDisplay.Double = 1;

 DataWriteMode = DR_NORMAL;
 lGPUstatusRet = 0x14802000;

 return 0;
}

void renderer_finish(void)
{
}

void renderer_notify_res_change(void)
{
}

static void check_skip_frame(unsigned int *list) {
    for (int i=0;i<CMD_DATA_COUNT;i++) {
      int count = 0;
      for (int cs=0;cs<12;cs++) {
        if ((skip_frame_data[i][cs]&SKIP_DATA_MASK[cs]) == (list[cs]&SKIP_DATA_MASK[cs])){
          count ++;
        }
        else {
          count = 0;
          break;
        }
      }
      if (count == 12 && !gpu.state.skip_frame) {
        gpu.state.skip_frame = 1;
        break;
      }
    }
}

static int pmt_cmd_count = 0;
void check_pmt_cmd(unsigned int cmd, unsigned int len, unsigned int *list) {
  if (gpu.state.dma_chain) {
    pmt_cmd_count = 0;
    gpu.state.dma_chain = 0;
    gpu.state.pmt_show = 0;
  }
  if (gpu.state.pmt_show)
    return;

  int pos = 0;
  for (int i=0;i<PMT_CMD[pmt_cmd_count][0];i++) {
    if ((PMT_CMD[pmt_cmd_count][i+1] & *(PMT_MASK[pmt_cmd_count] + i)) == (list[i] & *(PMT_MASK[pmt_cmd_count] + i))) {
		  pos ++;
    }
    else
      break;
  }
  if (pos >= PMT_CMD[pmt_cmd_count][0]) {
    pmt_cmd_count ++;
    if (pmt_cmd_count >= PMT_CMD_COUNT) {
      gpu.state.pmt_show = 1;
      pmt_cmd_count = 0;
    }
  }
  else
    pmt_cmd_count = 0;
}

extern const unsigned char cmd_lengths[256];

int do_cmd_list(unsigned int *list, int list_len, int *last_cmd)
{
  unsigned int cmd = 0, len;
  unsigned int *list_start = list;
  unsigned int *list_end = list + list_len;

  for (; list < list_end; list += 1 + len)
  {
    cmd = *list >> 24;
    len = cmd_lengths[cmd];
    if (list + 1 + len > list_end) {
      cmd = -1;
      break;
    }

#ifndef TEST
    if (cmd == 0xa0 || cmd == 0xc0)
      break; // image i/o, forward to upper layer
    else if ((cmd & 0xf8) == 0xe0)
      gpu.ex_regs[cmd & 7] = list[0];
#endif

    primTableJ[cmd]((void *)list);

    if ((g_gpu_patch_flag & 0x00000020) == 0x00000020) {
      check_pmt_cmd(cmd, len, list);
    }

    if (cmd==0x3c && !gpu.state.skip_frame && gpu.vram2)
      check_skip_frame(list);

    switch(cmd)
    {
      case 0x48 ... 0x4F:
      {
        u32 num_vertexes = 2;
        u32 *list_position = &(list[3]);

        while(1)
        {
          if(list_position >= list_end) {
            cmd = -1;
            goto breakloop;
          }

          if((*list_position & 0xf000f000) == 0x50005000)
            break;

          list_position++;
          num_vertexes++;
        }

        len += (num_vertexes - 2);
        break;
      }

      case 0x58 ... 0x5F:
      {
        u32 num_vertexes = 2;
        u32 *list_position = &(list[4]);

        while(1)
        {
          if(list_position >= list_end) {
            cmd = -1;
            goto breakloop;
          }

          if((*list_position & 0xf000f000) == 0x50005000)
            break;

          list_position += 2;
          num_vertexes++;
        }

        len += (num_vertexes - 2) * 2;
        break;
      }

#ifdef TEST
      case 0xA0:          //  sys -> vid
      {
        short *slist = (void *)list;
        u32 load_width = slist[4];
        u32 load_height = slist[5];
        u32 load_size = load_width * load_height;

        len += load_size / 2;
        break;
      }
#endif
    }
  }

breakloop:
  gpu.ex_regs[1] &= ~0x1ff;
  gpu.ex_regs[1] |= lGPUstatusRet & 0x1ff;

  *last_cmd = cmd;
  return list - list_start;
}

void renderer_sync_ecmds(uint32_t *ecmds)
{
  cmdTexturePage((unsigned char *)&ecmds[1]);
  cmdTextureWindow((unsigned char *)&ecmds[2]);
  cmdDrawAreaStart((unsigned char *)&ecmds[3]);
  cmdDrawAreaEnd((unsigned char *)&ecmds[4]);
  cmdDrawOffset((unsigned char *)&ecmds[5]);
  cmdSTP((unsigned char *)&ecmds[6]);
}

void renderer_update_caches(int x, int y, int w, int h)
{
}

void renderer_flush_queues(void)
{
}

void renderer_set_interlace(int enable, int is_odd)
{
}

#include "../../frontend/plugin_lib.h"

void renderer_set_config(const struct rearmed_cbs *cbs)
{
 iUseDither = cbs->gpu_peops.iUseDither;
 dwActFixes = cbs->gpu_peops.dwActFixes;
 isToShinDen = cbs->gpu_peops.isToShinDen;
 isBiosLogoEnd = cbs->gpu_peops.isBiosLogoEnd;
 scenes = &cbs->gpu_peops.scenes;
 regions = cbs->gpu_peops.regions;
 iTrimJaggyFrame = cbs->gpu_peops.iTrimJaggyFrame;
 if (cbs->pl_set_gpu_caps)
  cbs->pl_set_gpu_caps(0);
 set_vram(gpu.vram);
}
