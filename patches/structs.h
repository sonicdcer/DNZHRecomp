#ifndef RECOMP_STRUCTS
#define RECOMP_STRUCTS

#include "patches.h"

#define klabs(A) (((A) > 0) ? (A) : -(A))

#define CLAMP_MAX(A, B) (((A) > B) ? B : A)

#define CLAMP_MIN(A, B) (((A) < B) ? B : A)

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define PI 3.14159265359

#define SQ(x) ((x) * (x))

#define DEG2RAD(x) ((x) * (PI / 180.f))

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define ASPECT_RATIO (4.0f / 3.0f)

#define GFX_TASKS 2
#define DISPLAY_LIST_SIZE 0x1400

#define MAXWALLS 3912
#define MAXSECTORS 657
#define MAXPLAYERS 4
#define NUM_DMA_MSGS 256

#define CONTROL_PRESET_NUM 8
#define CONTROL_MAPPING_NUM 16

#define CONTROLLER_EEPROM_LONG_READ 1
#define CONTROLLER_EEPROM_LONG_WRITE 2
#define CONTROLLER_PFS_NUM_FILES 3
#define CONTROLLER_PFS_FREE_BLOCKS 4
#define CONTROLLER_PFS_FILE_STATE 5
#define CONTROLLER_PFS_DELETE_FILE 6
#define CONTROLLER_PFS_INIT_PAK 7
#define CONTROLLER_PFS_REPAIR_ID 8
#define CONTROLLER_PFS_READ_WRITE_FILE 9
#define CONTROLLER_PFS_ALLOCATE_FILE 10
#define CONTROLLER_PFS_FIND_FILE 11
#define CONTROLLER_MOTOR_INIT 12
#define CONTROLLER_GET_STATUS 13
#define COMPANY_CODE 0x3458 /*4X*/

#define __C__ 0xFF
#define GAMECODE 0x4E445A45 /*NDZE*/

#define DECL_STATIC_SEG_SYM(A) extern u8 A##_STATIC_START[]

#define GET_STATIC_SEG_SYM(A) ((s32) gStaticSegment + (s32) A##_STATIC_START)

#define IDLELOOP_STACKSIZE 0x1000
#define VILOOP_STACKSIZE 0x1000
#define MAINLOOP_STACKSIZE 0x8000
#define SCHEDULER_STACKSIZE 0x2000
#define NUM_DMA_MSGS 256
#define PHYSICAL_SEGMENT 0
#define STATIC_SEGMENT 1
#define FRAMEBUFFER_SEGMENT 2
#define OUTPUT_BUFFER_SIZE 65536
#define STATIC_SEGMENT_VRAM (STATIC_SEGMENT << 24)
#define FRAMEBUFFER_ALIGN 16
#define DEPTHBUFFER_ALIGN 256

#define FORNEXT_DEPTH 4

typedef f32 Matrix4f[4][4];
typedef f32 Vec4f[4];
typedef u8 Addr[];

typedef void (*ProcPointer)(void);

typedef struct {
    /*0x00*/ s16 dimx;
    /*0x02*/ s16 dimy;
    /*0x04*/ s32 offset;
} ModelTextureInfo;

typedef struct {
    /*0x00*/ s32 fileoff;
    /*0x04*/ u8* ramaddr;
    /*0x08*/ s16 unused;
    /*0x0A*/ s16 size;
} ModelVertexInfo;

typedef struct {
    /*0x00*/ s32 fileoff;
    /*0x04*/ u8* ramaddr;
    /*0x08*/ u16 unk8;
    /*0x0A*/ u16 unkA;
    /*0x0C*/ u16 texture_info_off;
    /*0x0E*/ u16 cmd_off;
    /*0x10*/ u16 lights_off;
    /*0x12*/ u16 vertex_size;
    /*0x14*/ u8 pad2[4];
    /*0x18*/ ModelVertexInfo* vertex_info;
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

typedef struct {
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

typedef struct {
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

typedef struct {
    Color primary;
    Color env;
} AlphaPalette;

typedef struct {
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

typedef struct {
    FogColor color[3];
    FogScale scale[3];
    s16 unk1E;
    u8 unk20;
    u8 pad;
} Fog;

typedef struct {
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

typedef struct {
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

typedef struct {
    s16 picnum;
    s16 sfxnum;
    char* actor;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} _11B300UnkStruct1;

typedef struct {
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

typedef struct {
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

typedef struct {
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
    char* mapname;
} MapChapter;

typedef struct {
    s32 flag;
    s32 unk4;
    s16 unk8;
    u16 unkA;
    s32* exec_ptr;
    s32* unk10;
    s32* unk14;
    s32* unk18;
    s32* unk1C;
    s32* unk20;
    s32* unk24;
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

typedef struct {
    s16 unk0;
    u8 unk2[8];
    s16 unkA[8];
} code0UnkStruct2;

typedef struct {
    u8* texture;
    u8* palette;
    s32 texoff;
    s32 paloff;
    s16 width;
    s16 height;
} _E0640UnkStruct;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} code0UnkStruct18;

typedef struct {
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
    void* unk70;
    s32 unk74;
    s32 unk78;
    void* unk7C;
    void* unk80;
    code0UnkStruct18* unk84;
    s32 unk88;
    u8* unk8C;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    Gfx* unkA4;
    u8 pad9[4];
    Lights1* unkAC;
} code0UnkStruct16;

typedef struct {
    u16 unk0;
    u16 id;
    u16 offset;
    u16 vtx_count;
    u16 dlist_count;
} _119280UnkStruct1;

typedef struct {
    /*0x0*/ u16 button;
    /*0x2*/ u16 button2;
    /*0x4*/ s16 stick_x;
    /*0x6*/ s16 stick_y;
} Controller;

typedef struct {
    unsigned short wave; /* wave number */
    unsigned short adsr; /* envelope number */
    unsigned char pan;   /* pan position */
    unsigned char pitch; /* semitone */
} drum_t;

typedef struct {
    unsigned long version; /* 16.16 version number */
    long num_channels;     /* number of channels in this song */
    long num_waves;        /* number of waves in table */

    /* offsets converted to pointers go here - changing these requires
       MusStartSong() to be changed! */
#define SONGHDR_COUNT 7                  /* number of pointers to convert */
#define SONGHDR_ADR(x) (&(x)->data_list) /* start address of pointer list */

    /* channel pointers */
    unsigned char** data_list;   /* channel data address list */
    unsigned char** volume_list; /* channel volume address list */
    unsigned char** pbend_list;  /* pitchbend address list */
    /* table pointers */
    unsigned char* env_table;   /* address of envelope table */
    drum_t* drum_table;         /* address of drum map table */
    unsigned short* wave_table; /* address of waveform lookup table */
    /* master track */
    unsigned char* master_track; /* address of master track */

    /* library workspace */
    unsigned long flags;
    unsigned long reserved1;
    unsigned long reserved2;
    unsigned long reserved3;
} song_t;

typedef struct {
    unsigned char header_name[16]; /* "Nu64 pointer bank" (or something like that)   */
    unsigned long flags;           /* 32 bit flags                                   */
    unsigned long wbk_name[3];     /* 12 byte ASCII name (currently unused)          */
    int count;                     /* number of samples contained in sample bank     */
    /* the three pointers below must be consecutive */
    unsigned char* basenote; /* address of corse tune array                    */
    float* detune;           /* address of fine tune array                     */
    ALWaveTable** wave_list; /* address of wave table pointer array            */
} ptr_bank_t;

typedef struct {
    unsigned char* fxdata;
    int priority;
} fx_t;

typedef struct {
    int number_of_components;
    int number_of_effects;
    int num_waves;
    unsigned long flags;
    ptr_bank_t* ptr_addr;
    unsigned short* wave_table;
    fx_t effects[1]; /* "number_of_components" sized array */
} fx_header_t;

typedef struct {
    /* 32bit values... */
    unsigned long channel_flag; /* new flag for overall channel control */
    unsigned char* pdata;
    ALWaveTable* pending;
    unsigned long channel_frame;

    int stopping;
    unsigned long volume_frame;
    unsigned long pitchbend_frame;
    int stopping_speed;

    float vib_amount;
    float pitchbend_precalc;
    float old_frequency;
    float base_note;

    float freqoffset;
    unsigned char* ppitchbend;
    unsigned char* pvolume;
    unsigned long note_end_frame;

    unsigned long note_start_frame;
    unsigned long handle;
    int priority;
    float last_note;

    float port_base;
    unsigned long release_frame;
    float env_attack_calc;
    float env_decay_calc;

    float env_release_calc;
    int env_speed_calc;
    float vibrato;
    float bendrange;

    float pitchbend;
    song_t* song_addr;
    fx_header_t* fx_addr;
    ptr_bank_t* sample_bank;

    unsigned char* pbase;
    drum_t* pdrums;
    unsigned char* ppitchbendbase;
    unsigned char* pvolumebase;

    float distort;
    unsigned long sweep_frame;
    // 16bit values...
    short temscale;
    unsigned short length;
    unsigned short channel_tempo;
    short volscale;

    unsigned short old_volume;
    unsigned short cont_vol_repeat_count;
    unsigned short cont_pb_repeat_count;
    unsigned short fx_number;
    unsigned short channel_tempo_save;
    unsigned short count;
    unsigned short fixed_length;
    unsigned short wave;

    short panscale;
    unsigned short cutoff;
    unsigned short endit;
    // 8bit values...
    unsigned char vib_delay;
    unsigned char ignore;

    unsigned char port;
    unsigned char transpose;
    unsigned char ignore_transpose;
    unsigned char velocity;
    unsigned char volume;
    unsigned char pan;
    unsigned char old_pan;
    unsigned char env_speed;
    unsigned char env_init_vol;
    unsigned char env_max_vol;
    unsigned char env_sustain_vol;
    unsigned char env_phase;
    unsigned char env_current;
    unsigned char env_count;
    unsigned char env_attack_speed;
    unsigned char env_decay_speed;

    unsigned char env_release_speed;
    unsigned char playing;
    unsigned char reverb; // wet/dry mix for alSynSetMix()
    unsigned char reverb_base;
    unsigned char old_reverb;
    unsigned char release_start_vol;
    unsigned char wobble_on_speed;
    unsigned char wobble_off_speed;
    unsigned char wobble_count;
    signed char wobble_current;
    unsigned char velocity_on;
    unsigned char default_velocity;
    unsigned char sweep_speed;
    unsigned char vib_speed; /* zero if not active*/
    unsigned char env_trigger_off;
    unsigned char trigger_off;

    signed char wobble_amount;
    unsigned char sweep_timer;
    unsigned char sweep_dir;
    unsigned char for_stack_count;

    float vib_precalc;

    /* for-next stuff all together */
    unsigned char* for_stack[FORNEXT_DEPTH];
    unsigned char* for_stackvol[FORNEXT_DEPTH];
    unsigned char* for_stackpb[FORNEXT_DEPTH];
    unsigned short for_vol_count[FORNEXT_DEPTH];
    unsigned short for_pb_count[FORNEXT_DEPTH];
    unsigned char for_count[FORNEXT_DEPTH];
    unsigned char for_volume[FORNEXT_DEPTH];
    float for_pitchbend[FORNEXT_DEPTH];

#ifndef SUPPORT_EFFECTS
    unsigned char padding[4]; /* pad for data cache */
#else
    unsigned long effect_type;
    float specialvib_amount;
    unsigned char specialvib_speed;
    unsigned char specialvib_delay;
    unsigned char last_volume;
    unsigned char vol_effect[4];
    unsigned char pitch_effect[4];
#endif
} channel_t;

typedef struct {
    s16 count;
    char** addr;
} ObjectiveStrInfo;

typedef struct {
    /*0x00*/ s32 fileoff;
    /*0x04*/ u8* ramaddr;
    /*0x08*/ s32 picanm;
    /*0x0C*/ s16 sizex;
    /*0x0E*/ s16 sizey;
    /*0x10*/ u16 filesize;
    /*0x12*/ u16 dimx;
    /*0x14*/ u16 dimy;
    /*0x16*/ u8 flags;
    /*0x18*/ u16 tile;
} TileInfo;

typedef struct {
    /*0x00*/ u8* rom_start;
    /*0x04*/ u8* rom_end;
    /*0x08*/ s32 sector_offset;
    /*0x0C*/ s32 wall_offset;
    /*0x10*/ s32 sprite_offset;
    /*0x14*/ s32 sectors;
    /*0x18*/ s32 sprites;
    /*0x1C*/ s32 walls;
    /*0x20*/ s32 xpos;
    /*0x24*/ s32 ypos;
    /*0x28*/ s32 zpos;
    /*0x2C*/ s32 ang;
    /*0x30*/ f32 skytop_r;
    /*0x34*/ f32 skytop_g;
    /*0x38*/ f32 skytop_b;
    /*0x3C*/ f32 skybottom_r;
    /*0x40*/ f32 skybottom_g;
    /*0x44*/ f32 skybottom_b;
} MapInfo;

typedef struct {
    /*0x00*/ s16* unk0;
    /*0x04*/ s16 unk4;
    /*0x06*/ s16 unk6;
} _11D520UnkStruct1;

typedef struct {
    /*0x00*/ u8 unk0;
    /*0x01*/ u8 unk1;
    /*0x02*/ u8 unk2;
} code1UnkStruct4;

typedef struct {
    /*0x00*/ s16 unk0;
    /*0x02*/ s16 unk2;
    /*0x04*/ s16 unk4;
    /*0x06*/ s16 unk6;
} _11B300UnkStruct2;

typedef union {
    struct {
        char* turn_left;
        char* turn_right;
        char* move_forward;
        char* move_back;
        char* move_left;
        char* move_right;
        char* look_up;
        char* look_down;
        char* jump;
        char* fire;
        char* open;
        char* next_weapon;
        char* last_weapon;
        char* next_item;
        char* previous_item;
        char* activate_item;
    } u;
    char* mapping[16];
} ControlMapping;

typedef struct {
    /*0x000*/ u16 unk0;
    /*0x002*/ u16 unk2;
    /*0x004*/ u16 unk4[24][3];
    /*0x148*/ u16 unk148[8];
    /*0x164*/ u16 enemies_total;
    /*0x166*/ u16 babes_total;
    /*0x168*/ u16 secrets_total;
    /*0x172*/ s32 unk172; /*time_taken*/
    /*0x176*/ u16 enemies_killed;
    /*0x178*/ u16 babes_saved;
    /*0x180*/ u16 secrets_found;
    /*0x182*/ u8 unk182;
} code1UnkStruct2;

typedef struct {
    /*0x0000*/ u16 unk0;
    /*0x0002*/ u16 unk2;
    /*0x0004*/ code1UnkStruct2 unk4[22];
    /*0x0FD4*/ u8 unkFD4;
    /*0x0FD5*/ u8 unkFD5; /*mapnum*/
    /*0x0FD6*/ u8 unkFD6;
    /*0x0FD7*/ u8 unkFD7;
    /*0x0FD8*/ s32 unlocked_skin;
    /*0x0FDC*/ s32 unlocked_cheat;
    /*0x0FE0*/ u16 unlocked_cheat_weapons;
    /*0x0FE4*/ s32 time_machine_part;
    /*0x0FE8*/ Config unkFE8;
    /*0x103A*/ u8 unk103A;
    /*0x103C*/ u8 pad2;
} code1UnkStruct3;
typedef struct {
    code1UnkStruct3 unk0;

} code1UnkStruct7;

#endif