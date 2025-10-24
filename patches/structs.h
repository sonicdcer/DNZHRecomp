#ifndef RECOMP_STRUCTS
#define RECOMP_STRUCTS

#include "patches.h"

#define klabs(A) (((A) > 0) ? (A) : -(A))

#define CLAMP_MAX(A, B) \
    (((A) > B) ? B : A)

#define CLAMP_MIN(A, B) \
    (((A) < B) ? B : A)

#define ARRAY_COUNT(arr) \
    (s32)(sizeof(arr) / sizeof(arr[0]))

#define PI 3.14159265359

#define SQ(x) ((x) * (x))

#define DEG2RAD(x) ((x) * (PI / 180.f))

#define MAXWALLS 3912
#define MAXSECTORS 657
#define MAXPLAYERS 4

typedef f32 Matrix4f[4][4];
typedef f32 Vec4f[4];

typedef struct
{
    /*0x00*/ s16 dimx;
    /*0x02*/ s16 dimy;
    /*0x04*/ s32 offset;
} ModelTextureInfo;

typedef struct {
    /*0x00*/ s32 fileoff;
    /*0x04*/ u8 *ramaddr;
    /*0x08*/ s16 unused;
    /*0x0A*/ s16 size;
} ModelVertexInfo;

typedef struct {
    /*0x00*/ s32 fileoff;
    /*0x04*/ u8 *ramaddr;
    /*0x08*/ u16 unk8;
    /*0x0A*/ u16 unkA;
    /*0x0C*/ u16 texture_info_off;
    /*0x0E*/ u16 cmd_off;
    /*0x10*/ u16 lights_off;
    /*0x12*/ u16 vertex_size;
    /*0x14*/ u8 pad2[4];
    /*0x18*/ ModelVertexInfo *vertex_info;
    /*0x1C*/ u8 pad3[4];
    /*0x20*/ s8 lock;
    /*0x21*/ u8 pad4[3];
    /*0x24*/ s16 xmin;
    /*0x26*/ s16 ymin;
    /*0x28*/ s16 zmin;
    /*0x2A*/ s16 xmax;
    /*0x2C*/ s16 ymax;
    /*0x2E*/ s16 zmax;
} ModelInfo;

typedef struct {
    /*0x00*/ s8 n[3]; /*normal*/
    /*0x03*/ s8 unused[3];
} ModelLight;

typedef struct
{
    /*0x00*/ s32 ceilingz;
    /*0x04*/ s32 floorz;
    /*0x08*/ s16 wallptr;
    /*0x0A*/ s16 wallnum;
    /*0x0C*/ s16 ceilingstat;
    /*0x0E*/ s16 floorstat;
    /*0x10*/ s16 ceilingpicnum;
    /*0x12*/ s16 ceilingheinum;
    /*0x14*/ s16 floorpicnum;
    /*0x16*/ s16 floorheinum;
    /*0x18*/ s16 unk18; /*lotag?*/
    /*0x1A*/ s16 unk1A; /*hitag?*/
    /*0x1C*/ s16 unk1C; /*extra?*/
    /*0x1E*/ u16 floorvtxptr;
    /*0x20*/ u16 ceilingvtxptr;
    /*0x22*/ u8 ceilingshade;
    /*0x23*/ u8 ceilingpal;
    /*0x24*/ u8 pad[2];
    /*0x26*/ u8 floorshade;
    /*0x27*/ u8 floorpal;
    /*0x28*/ u8 pad2[2];
    /*0x2A*/ u8 unk2A;
    /*0x2B*/ u8 floorvtxnum;
    /*0x2C*/ u8 ceilingvtxnum;
    /*0x2D*/ u8 pad3[3];
} SectorType;

typedef struct
{
    /*0x0000*/ Mtx mtx1[MAXPLAYERS];
    /*0x0100*/ Mtx mtx2[MAXPLAYERS];
    /*0x0200*/ LookAt lookat[MAXPLAYERS][2];
    /*0x0300*/ Mtx mtx6;
    /*0x0340*/ Mtx mtx7;
    /*0x0380*/ Mtx mtx8;
    /*0x03C0*/ u8 pad1[192];
    /*0x0480*/ Mtx mtx3[256];
    /*0x4480*/ Light light[128];
    /*0x4C80*/ Mtx mtx4;
    /*0x4CC0*/ Mtx projection;
    /*0x4D00*/ Mtx viewing;
    /*0x4D40*/ Mtx identity;
    /*0x4D80*/ Mtx scale;
    /*0x4DC0*/ Mtx mtx5[128]; /*?*/
} Dynamic;

#endif