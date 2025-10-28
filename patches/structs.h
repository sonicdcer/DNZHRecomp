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

typedef void (*ProcPointer)(void);

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

typedef struct {
    u8 r, g, b;
} Color;

typedef struct
{
             Color primary;
             Color env;
} AlphaPalette;

typedef struct
{
             u16 r;
             u16 g;
             u16 b;
} GlobalPalette;

typedef struct {
    s16 r;
    s16 g;
    s16 b;
} FogColor;

typedef struct {
    s16 nr;
    s16 fr;
} FogScale;

typedef struct
{
    FogColor color[3];
    FogScale scale[3];
    s16 unk1E;
    u8 unk20;
    u8 pad;
} Fog;

typedef struct
{
             s32 unk0;
             s32 unk4;
             s32 unk8;
             s32 unkC;
             s32 unk10;
             s32 unk14;
             s16 picnum;
             s32 height;
             Color fog;
} Cloud;

typedef struct
{
             s32 xpos;
             s32 ypos;
             s32 zpos;
             s32 xvect;
             s32 yvect;
             s32 zvect;
             s32 unk18;
             s32 unk1C;
             s32 unk20;
             s32 unk24;
             s32 unk28;
             s32 unk2C;
             s32 unk30;
             s16 cursectnum;
             s16 unk36;
             s16 ang;
             s16 unk3A;
             s16 unk3C;
             s16 unk3E;
             s32 unk40;
             u8 unk44;
             u8 unk45;
             s16 unk46;
             s16 unk48;
             s16 unk4A;
             s16 skin;
             s16 unk4E;
             s16 unk50;
             s16 unk52;
             u8 unk54;
             u8 unk55;
             u8 unk56;
             u8 unk57;
             u8 unk58;
             u8 unk59;
             u8 unk5A;
             u8 unk5B;
             u8 unk5C;
             s16 unk5E;
             u8 third_person;
             u8 unk61;
             f32 unk64;
             s16 unk68;
             s16 unk6A;
             u8 unk6C;
             s16 unk6E;
             s16 unk70;
             s16 unk72;
             s16 unk74;
             s16 unk76;
             f32 unk78;
             f32 unk7C;
             u8 unk80;
             s16 unk82;
             s16 unk84;
             s16 unk86;
             u8 keys[17];
             u8 pad[2];
} Player;

typedef struct
{
             s16 picnum;
             s16 sfxnum;
             char *actor;
             u8 unk8;
             u8 unk9;
             u8 unkA;
             u8 unkB;
} _11B300UnkStruct1;

typedef struct
{
             s32 x;
             s32 y;
             s32 z;
             s16 cstat;
             s16 picnum;
             s16 sectnum;
             s16 statnum;
             s16 ang;
             s16 unk16;
             s16 unk18;
             s16 unk1A;
             s16 unk1C;
             s16 lotag;
             s16 hitag;
             s16 unk22;
             u8 unk24;
             u8 unk25;
             u8 clipdist;
             u8 xrepeat;
             u8 yrepeat;
             u8 unk29;
             u8 unk2A;
             u8 unk2B;
} SpriteType;

typedef struct
{
    struct {
                 u8 main;
                 u8 options_2P;
                 u8 select_single_multi_player;
                 u8 multiplayer_options;
                 u8 unk4;
                 u8 unk5;
                 u8 controller_config;
                 u8 options_1P;
                 u8 select_difficulty;
                 u8 select_multiplayer_gametype;
                 u8 unkA;
                 u8 unkB;
                 u8 unkC;
                 u8 unkD;
                 u8 select_player;
                 u8 unkF;
                 u8 player_setup;
                 u8 unk11;
                 u8 cheats;
                 u8 cheats_others;
                 u8 cheats_game_type;
                 u8 cheats_weapons;
    } menuIndex;

             u16 sound;
             u16 mastervol;
             u16 musicvol;
             u16 rumblepak;

    struct {
                 u16 radar;
                 u16 time_limit;
                 u16 frag_count;
                 u16 split_2P;
                 u16 split_3P;
                 u16 friendly_fire;
                 u16 players;
    } multiplayer;

             u16 unused;
             u16 controller_preset[4];
             u16 crosshair[4];
             u16 autoaim[4];
             u16 autocenter[4];
             u16 difficulty;
             u8 unk50;
} Config;

typedef struct
{
             u16 enemies_killed;
             u16 enemies_total;
             u16 babes_saved;
             u16 babes_total;
             u16 secrets_found;
             u16 secrets_total;
             s32 unkC;
             u8 unk10;
} code0UnkStruct4;

typedef unsigned long musHandle;

typedef struct {
             u16 chapter;
             char *mapname;
} MapChapter;

typedef struct
{
             s32 flag;
             s32 unk4;
             s16 unk8;
             u16 unkA;
             s32 *exec_ptr;
             s32 *unk10;
             s32 *unk14;
             s32 *unk18;
             s32 *unk1C;
             s32 *unk20;
             s32 *unk24;
             s16 unk28;
             s16 unk2A;
             s16 unk2C;
             s16 unk2E;
             s16 unk30;
             s16 unk32;
             s16 unk34;
             s16 unk36;
             s32 unk38;
             s32 unk3C;
             s32 unk40;
             s32 unk44;
             s32 unk48;
             s32 unk4C;
             s32 unk50;
             s32 unk54;
             s32 unk58;
             s32 unk5C;
             s32 unk60;
             s32 unk64;
             s32 unk68;
             musHandle unk6C;
             musHandle unk70;
             s32 unk74;
             s32 unk78;
             s16 unk7C;
             s16 unk7E;
             s16 unk80;
             s16 unk82;
             s16 unk84;
             s16 unk86;
             s16 unk88;
             s16 unk8A;
             s16 unk8C;
             s16 unk8E;
             s16 unk90;
             u8 unk92;
             u8 unk93;
             u8 unk94;
             u8 unk95;
             u8 unk96;
             u8 unk97;
             u8 unk98;
             u8 unk99;
             u8 unk9A;
             u8 unk9B;
             u8 unk9C;
             u8 unk9D;
             u8 unk9E;
             u8 unk9F;
             u8 unkA0;
             u8 unkA1;
             u8 unkA2;
             u8 unkA3;
} Actor;

typedef struct
{
             s16 unk0;
             u8 unk2[8];
             s16 unkA[8];
} code0UnkStruct2;

typedef struct
{
             u8 *texture;
             u8 *palette;
             s32 texoff;
             s32 paloff;
             s16 width;
             s16 height;
} _E0640UnkStruct;

typedef struct
{
             s16 x;
             s16 y;
             s16 z;
} code0UnkStruct18;

typedef struct
{
             s8 unk0;
             s32 unk4;
             u32 unk8;
             s32 unkC;
             u8 unk10;
             u8 unk11;
             u8 unk12;
             u8 pad2[1];
             s32 unk14;
             u8 pad3[28];
             f32 unk34;
             f32 unk38;
             f32 unk3C;
             f32 unk40;
             f32 unk44;
             f32 unk48;
             f32 unk4C;
             f32 unk50;
             f32 unk54;
             f32 unk58;
             f32 unk5C;
             f32 unk60;
             f32 unk64;
             Color unk68;
             Color unk6B;
             u8 pad7[2];
             void *unk70;
             s32 unk74;
             s32 unk78;
             void *unk7C;
             void *unk80;
             code0UnkStruct18 *unk84;
             s32 unk88;
             u8 *unk8C;
             s32 unk90;
             s32 unk94;
             s32 unk98;
             s32 unk9C;
             s32 unkA0;
             Gfx *unkA4;
             u8 pad9[4];
             Lights1 *unkAC;
} code0UnkStruct16;

typedef struct
{
    u16 unk0;
    u16 id;
    u16 offset;
    u16 vtx_count;
    u16 dlist_count;
} _119280UnkStruct1;

#endif