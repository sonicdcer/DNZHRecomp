#include "patches.h"

#if 0
RECOMP_PATCH void main_80000C74(void)
{
    recomp_printf("FramebufferIndex: %d\n", _framebufferIndex_000BE020);
    gDPPipeSync(gpDisplayList++);
    gDPSetCycleType(gpDisplayList++, G_CYC_FILL);
    gDPSetRenderMode(gpDisplayList++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetColorImage(gpDisplayList++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth, OS_K0_TO_PHYSICAL(gDepthBuffer));
    gDPSetFillColor(gpDisplayList++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
    gDPFillRectangle(gpDisplayList++, 12, 12, gScreenWidth - 12, gScreenHeight - 12);
    gDPPipeSync(gpDisplayList++);
    gDPSetColorImage(gpDisplayList++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth, OS_K0_TO_PHYSICAL(_framebuffer[_framebufferIndex_000BE020]));
    gDPSetCycleType(gpDisplayList++, G_CYC_2CYCLE);
}
#endif

#if 1
RECOMP_PATCH void func_80000DDC(void) {
    // recomp_printf("FramebufferIndex: %d\n", _framebufferIndex_000BE020);
    gGraphicsOption = 1; // force graphics to be Medium

#if DEBUG_MENU == 1
    gDebugMenu = 1;
#endif

    gEXEnable(gpDisplayList++);              // @recomp
    gEXSetRDRAMExtended(gpDisplayList++, 1); // @recomp
    gEXSetRefreshRate(gpDisplayList++, 60 / 1);
    gDPSetColorImage(gpDisplayList++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenWidth,
                     OS_K0_TO_PHYSICAL(_framebuffer[_framebufferIndex_000BE020]));
    if (D_800BD3E8 != 0) {
        gDPSetCycleType(gpDisplayList++, G_CYC_FILL);
        gDPSetFillColor(gpDisplayList++, GPACK_RGBA5551(_red_000BDFEC, _green_000BDFED, _blue_000BDFEE, 1) << 16 |
                                             GPACK_RGBA5551(_red_000BDFEC, _green_000BDFED, _blue_000BDFEE, 1));
        gDPFillRectangle(gpDisplayList++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    }
}
#endif

// recomp_load_overlays(0xEB300, (u32*) 0x801C0D80, 0xBA70);

#if 0
/*80002548*/
/* @theboy181 - 60fps render, fixed 30fps logic (frame-rate independent) */
RECOMP_PATCH void mainLoop(void *arg)
{
    s16 i, j;
    s16 *count;
    s16 count2;
    s32 *addr_;
    s32 size;
    ObjectiveStrInfo *msg_;
    s32 offset_;
    u8 *temp;

    recomp_load_overlays(0xEB300, (u32*) 0x801C0D80, 0xBA70);

    osCreateMesgQueue(&gDmaMessageQ, _dmaMessages, NUM_DMA_MSGS);

    D_80197D4C = code1_VRAM;
    D_8010571C = (u8 *)main_80000450;
    D_80138818 = (u32)(code1_VRAM - (u8 *)main_80000450) >> 10;
    gStaticSegment = (u8 *)code1_VRAM_END;
    size = static_ROM_END - static_ROM_START;
    gCacheMemStart = (u8 *)((s32)(&gStaticSegment[size] + 0x3F) & ~0x3F);

    // osInvalICache(code1_TEXT_START, code1_TEXT_END - code1_TEXT_START);
    readRom(code1_VRAM, code1_ROM_START, code1_ROM_END - code1_ROM_START);
    Bmemset(code1_BSS_START, 0, code1_BSS_END - code1_BSS_START);
    readRom(code1_VRAM_END, static_ROM_START, size);

    gpTileInfo = (TileInfo *)GET_STATIC_SEG_SYM(gTileInfo);
    gpKeyStrInfo = (char ***)GET_STATIC_SEG_SYM(gKeyStrInfo);
    gpObjectiveStrInfo = (ObjectiveStrInfo *)GET_STATIC_SEG_SYM(gObjectiveStrInfo);

    count = (s16 *)GET_STATIC_SEG_SYM(gWeaponStrInfoCount);
    gpWeaponStrInfo = (char **)GET_STATIC_SEG_SYM(gWeaponStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpWeaponStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    gpMapStrInfo = (char **)GET_STATIC_SEG_SYM(gMapStrInfo);

    for (i = 0; i < ARRAY_COUNT(gMapStrInfo); i++)
    {
        s32 *addr = (s32 *)gpMapStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    i = 0;
    addr_ = (s32 *)gpKeyStrInfo;
    msg_ = gpObjectiveStrInfo;
    offset_ = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
    while (i < ARRAY_COUNT(gMapStrInfo))
    {
        ObjectiveStrInfo *msg;
        addr_[i] += offset_;
        *(s32 *)&msg_[i].addr += offset_;

        for (j = 0; j < 17 - 1; j++)
        {
            s32 *addr = (s32 *)addr_[i];
            addr[j] += offset_;
        }

        if (i)
        {
        }
        msg = msg_;
        for (j = 0; j < msg[i].count; j++)
        {
            s32 *addr = (s32 *)msg[i].addr;
            addr[j] += offset_;
        }

        i++;
    }

    gpSinTable = (s16 *)GET_STATIC_SEG_SYM(gSinTable);
    gpRadaRang = (s16 *)GET_STATIC_SEG_SYM(gRadarang);
    gpGlobalPalette = (GlobalPalette *)GET_STATIC_SEG_SYM(gGlobalPalette);
    gpAlphaPalette = (AlphaPalette *)GET_STATIC_SEG_SYM(gAlphaPalette);
    D_8012F6E4 = (_11B300UnkStruct1 *)GET_STATIC_SEG_SYM(D_01025BA0);
    count2 = *(s16 *)GET_STATIC_SEG_SYM(D_01025CFC);
    D_80138780 = count2;

    temp = gStaticSegment;
    for (i = 0; i < count2; i++)
    {
        _11B300UnkStruct1 *unk = (_11B300UnkStruct1 *)(temp + (s32)D_01025BA0_STATIC_START);
        s32 offset = (s32)temp - STATIC_SEGMENT_VRAM;
        *(s32 *)&unk[i].actor += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(gActionStrInfoCount);
    gpMapInfo = (MapInfo *)GET_STATIC_SEG_SYM(gMapInfo);
    gpActionStrInfo = (char **)GET_STATIC_SEG_SYM(gActionStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpActionStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    D_801ACBD8 = (_11D520UnkStruct1 *)GET_STATIC_SEG_SYM(D_01026910);

    for (i = 0; i < ARRAY_COUNT(D_01026910); i++)
    {
        s32 *addr = (s32 *)D_801ACBD8;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i * 2] += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(D_0102583C);
    D_801AE8F0 = (s16 *)GET_STATIC_SEG_SYM(D_01024590);
    D_80197DE8 = (s16 *)GET_STATIC_SEG_SYM(D_010245E8);
    D_801C0D70 = (_11B300UnkStruct2 *)GET_STATIC_SEG_SYM(D_0102464C);
    D_80129808 = (s16 **)GET_STATIC_SEG_SYM(D_0102578C);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)D_80129808;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(gLicenceStrInfoCount);
    D_801AD474 = (s16 *)GET_STATIC_SEG_SYM(D_010247AC);
    D_80105550 = (s16 *)GET_STATIC_SEG_SYM(D_01025734);
    D_800FF528 = (s32 *)GET_STATIC_SEG_SYM(D_01025840);
    D_8013F920 = (s16 *)GET_STATIC_SEG_SYM(D_010258D8);
    D_8012DF00 = (s16 *)GET_STATIC_SEG_SYM(D_01025908);
    D_8012E150 = (s16 *)GET_STATIC_SEG_SYM(D_01025968);
    gpLicenceStrInfo = (char **)GET_STATIC_SEG_SYM(gLicenceStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpLicenceStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(gCreditStrInfoCount);
    gpCreditStrInfo = (char **)GET_STATIC_SEG_SYM(gCreditStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpCreditStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    D_801CE5E8 = (_119280UnkStruct1 *)GET_STATIC_SEG_SYM(D_01022510);
    D_80138778 = (u8 *)GET_STATIC_SEG_SYM(D_01022790);
    gpControlPreset = (ControlMapping *)GET_STATIC_SEG_SYM(gControlPreset);

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 16; j++)
        {
            s32 *addr = (s32 *)gpControlPreset;
            s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
            *(addr + (i * 16) + j) += offset;
        }
    }

    allocMemory(SCREEN_WIDTH, SCREEN_HEIGHT, DISPLAY_LIST_SIZE * 2, 0);
    osCreateScheduler(&gScheduler, &_schedulerStack_0000A50F[SCHEDULER_STACKSIZE / sizeof(u64)], 40, _viMode_0000C937, (u8)1);
    osViBlack(1U);
    osCreateThread(&_viLoopThread_0000935F, 7, _viLoop, arg, &_viLoopThreadStack_0000950F[VILOOP_STACKSIZE / sizeof(u64)], 20);
    initAudio();
    configInitialize();
    controller_8008AD94();
    controller_8008A3EC("DUKE ZERO HOUR.A", &D_801CC930.unk0, sizeof(code1UnkStruct3));

    switch (osTvType)
    {
    case OS_TV_PAL:  D_801B0815 = 0; break;
    case OS_TV_NTSC: D_801B0815 = 1; break;
    case OS_TV_MPAL: D_801B0815 = 1; break;
    }

    osCreateMesgQueue(&D_8010A920, &D_801C0D64, 1);
    osCreateMesgQueue(&_retraceMsgQ, _retraceMessages, NUM_DMA_MSGS);
    osScAddClient(&gScheduler, &_retraceClient_0000C50F, &_retraceMsgQ);
    osStartThread(&_viLoopThread_0000935F);
    main_80000A94();
    func_800356EC();
    engine_8002B680();
    main_80001CFC();
    main_80000450();
    func_8000071C();
    func_80002494();
    gLoadMapNum = 0;

    /* --------------------------------------------------------------
       Dynamic frame pacing: 60 Hz render, fixed 30 Hz logic
       -------------------------------------------------------------- */
    {
        const s32 LOGIC_HZ = 30;
        s32 viHz = 60;
        s32 viDelta;
        s32 accumulator = 0; /* counts VI ticks */
        s32 ticksPerLogic = viHz / LOGIC_HZ;

        do
        {
            if (D_800DEDE0)
            {
                if (D_800DEDE0 == 2)
                    func_801C9B48();
                if (D_800DEDE0 == 3)
                    func_801C9E7C();
                if (D_800DEDE0 == 4)
                {
                    D_800BD3E8 = 0;
                    main_80000610();
                    D_800BD3F0_000BDFF0 = 0;
                    func_801C9B48();
                }
                loadMap(gLoadMapNum);
                D_800DEDE0 = 0;
                D_801A1970 = 1;
            }

            D_80138788 = D_800FE9E0;
            viDelta = D_800FE9E0 - D_801AE498;
            if (viDelta < 0)
                viDelta = 0;

            accumulator += viDelta;
            D_801AE498 = D_80138788;

            /* catch up logic if we fell behind */
            while (accumulator >= ticksPerLogic)
            {
                func_800017AC(); /* game logic @30Hz */
                accumulator -= ticksPerLogic;
            }

            func_80001AF8();
            func_80000F00();

            if (D_800BD3FC_000BDFFC != 0)
            {
                osRecvMesg(&D_8010A920, NULL, OS_MESG_BLOCK);
                D_800BD3FC_000BDFFC = 0;

                if (D_80119A5C != 0)
                    D_80119A5C--;

                if (_framebufferCount_000BDFD0 < 3)
                {
                    if (_retraceMsgQ.validCount >= _retraceMsgQ.msgCount)
                        osRecvMesg(&_retraceMsgQ, NULL, OS_MESG_BLOCK);
                    osRecvMesg(&_retraceMsgQ, NULL, OS_MESG_BLOCK);
                }
            }

            _createGfxTask();
            D_800BD3FC_000BDFFC = 1;
            D_800BD428_000BE028 = gGfxTaskIndex;
            gGfxTaskIndex ^= 1;
            _framebufferIndex_000BE020++;
            if (_framebufferIndex_000BE020 == _framebufferCount_000BDFD0)
                _framebufferIndex_000BE020 = 0;

        } while (1);
    }
}
#endif

// Original function
#if 0
RECOMP_PATCH void mainLoop(void *arg)
{
    s16 i, j;
    s16 *count;
    s16 count2;
    s32 *addr_;
    s32 size;
    ObjectiveStrInfo *msg_;
    s32 offset_;
    u8 *temp;

    recomp_load_overlays(0xEB300, (u32*) 0x801C0D80, 0xBA70);

    osCreateMesgQueue(&gDmaMessageQ, _dmaMessages, NUM_DMA_MSGS);

    D_80197D4C = code1_VRAM;
    D_8010571C = (u8 *)main_80000450;
    D_80138818 = (u32)(code1_VRAM - (u8 *)main_80000450) >> 10;
    gStaticSegment = (u8 *)code1_VRAM_END;
    size = static_ROM_END - static_ROM_START;
    gCacheMemStart = (u8 *)((s32)(&gStaticSegment[size] + 0x3F) & ~0x3F);

    osInvalICache(code1_TEXT_START, code1_TEXT_END - code1_TEXT_START);
    readRom(code1_VRAM, code1_ROM_START, code1_ROM_END - code1_ROM_START);
    Bmemset(code1_BSS_START, 0, code1_BSS_END - code1_BSS_START);
    readRom(code1_VRAM_END, static_ROM_START, size);

    gpTileInfo = (TileInfo *)GET_STATIC_SEG_SYM(gTileInfo);
    gpKeyStrInfo = (char ***)GET_STATIC_SEG_SYM(gKeyStrInfo);
    gpObjectiveStrInfo = (ObjectiveStrInfo *)GET_STATIC_SEG_SYM(gObjectiveStrInfo);

    count = (s16 *)GET_STATIC_SEG_SYM(gWeaponStrInfoCount);
    gpWeaponStrInfo = (char **)GET_STATIC_SEG_SYM(gWeaponStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpWeaponStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    gpMapStrInfo = (char **)GET_STATIC_SEG_SYM(gMapStrInfo);

    for (i = 0; i < ARRAY_COUNT(gMapStrInfo); i++)
    {
        s32 *addr = (s32 *)gpMapStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    i = 0;
    addr_ = (s32 *)gpKeyStrInfo;
    msg_ = gpObjectiveStrInfo;
    offset_ = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
    while (i < ARRAY_COUNT(gMapStrInfo))
    {
        ObjectiveStrInfo *msg;
        addr_[i] += offset_;
        *(s32 *)&msg_[i].addr += offset_;

        for (j = 0; j < 17-1; j++)
        {
            s32 *addr = (s32 *)addr_[i];
            addr[j] += offset_;
        }

        /*FAKEMATCH*/
        if (i)
        {
        }
        msg = msg_;
        for (j = 0; j < msg[i].count; j++)
        {
            s32 *addr = (s32 *)msg[i].addr;
            addr[j] += offset_;
        }

        i++;
    }

    gpSinTable = (s16 *)GET_STATIC_SEG_SYM(gSinTable);
    gpRadaRang = (s16 *)GET_STATIC_SEG_SYM(gRadarang);
    gpGlobalPalette = (GlobalPalette *)GET_STATIC_SEG_SYM(gGlobalPalette);
    gpAlphaPalette = (AlphaPalette *)GET_STATIC_SEG_SYM(gAlphaPalette);
    D_8012F6E4 = (_11B300UnkStruct1 *)GET_STATIC_SEG_SYM(D_01025BA0);
    count2 = *(s16 *)GET_STATIC_SEG_SYM(D_01025CFC);
    D_80138780 = count2;

    temp = gStaticSegment;
    for (i = 0; i < count2; i++)
    {
        /*FAKEMATCH*/
        _11B300UnkStruct1 *unk = (_11B300UnkStruct1 *)(temp + (s32)D_01025BA0_STATIC_START);
        s32 offset = (s32)temp - STATIC_SEGMENT_VRAM;
        *(s32 *)&unk[i].actor += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(gActionStrInfoCount);
    gpMapInfo = (MapInfo *)GET_STATIC_SEG_SYM(gMapInfo);
    gpActionStrInfo = (char **)GET_STATIC_SEG_SYM(gActionStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpActionStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    D_801ACBD8 = (_11D520UnkStruct1 *)GET_STATIC_SEG_SYM(D_01026910);

    for (i = 0; i < ARRAY_COUNT(D_01026910); i++)
    {
        s32 *addr = (s32 *)D_801ACBD8;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i*2] += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(D_0102583C);
    D_801AE8F0 = (s16 *)GET_STATIC_SEG_SYM(D_01024590);
    D_80197DE8 = (s16 *)GET_STATIC_SEG_SYM(D_010245E8);
    D_801C0D70 = (_11B300UnkStruct2 *)GET_STATIC_SEG_SYM(D_0102464C);
    D_80129808 = (s16 **)GET_STATIC_SEG_SYM(D_0102578C);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)D_80129808;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(gLicenceStrInfoCount);
    D_801AD474 = (s16 *)GET_STATIC_SEG_SYM(D_010247AC);
    D_80105550 = (s16 *)GET_STATIC_SEG_SYM(D_01025734);
    D_800FF528 = (s32 *)GET_STATIC_SEG_SYM(D_01025840);
    D_8013F920 = (s16 *)GET_STATIC_SEG_SYM(D_010258D8);
    D_8012DF00 = (s16 *)GET_STATIC_SEG_SYM(D_01025908);
    D_8012E150 = (s16 *)GET_STATIC_SEG_SYM(D_01025968);
    gpLicenceStrInfo = (char **)GET_STATIC_SEG_SYM(gLicenceStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpLicenceStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    count = (s16 *)GET_STATIC_SEG_SYM(gCreditStrInfoCount);
    gpCreditStrInfo = (char **)GET_STATIC_SEG_SYM(gCreditStrInfo);

    for (i = 0; i < *count; i++)
    {
        s32 *addr = (s32 *)gpCreditStrInfo;
        s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
        addr[i] += offset;
    }

    D_801CE5E8 = (_119280UnkStruct1 *)GET_STATIC_SEG_SYM(D_01022510);
    D_80138778 = (u8 *)GET_STATIC_SEG_SYM(D_01022790);
    gpControlPreset = (ControlMapping *)GET_STATIC_SEG_SYM(gControlPreset);

    for (i = 0; i < CONTROL_PRESET_NUM; i++)
    {
        for (j = 0; j < CONTROL_MAPPING_NUM; j++)
        {
            s32 *addr = (s32 *)gpControlPreset;
            s32 offset = (s32)gStaticSegment - STATIC_SEGMENT_VRAM;
            *(addr + (i*CONTROL_MAPPING_NUM) + j) += offset;
        }
    }

    allocMemory(SCREEN_WIDTH, SCREEN_HEIGHT, DISPLAY_LIST_SIZE*2, 0);
    osCreateScheduler(&gScheduler, &_schedulerStack_0000A50F[SCHEDULER_STACKSIZE / sizeof(u64)], 40, _viMode_0000C937, (u8)1);
    osViBlack(1U);
    osCreateThread(&_viLoopThread_0000935F, 7, _viLoop, arg, &_viLoopThreadStack_0000950F[VILOOP_STACKSIZE / sizeof(u64)], 20);
    initAudio();
    configInitialize();
    controller_8008AD94();
    controller_8008A3EC("DUKE ZERO HOUR.A", &D_801CC930.unk0, sizeof(code1UnkStruct3));
    switch (osTvType)
    {
    case OS_TV_PAL:
        D_801B0815 = 0;
        break;
    case OS_TV_NTSC:
        D_801B0815 = 1;
        break;
    case OS_TV_MPAL:
        D_801B0815 = 1;
        break;
    }

    osCreateMesgQueue(&D_8010A920, &D_801C0D64, 1);
    osCreateMesgQueue(&_retraceMsgQ, _retraceMessages, NUM_DMA_MSGS);
    osScAddClient(&gScheduler, &_retraceClient_0000C50F, &_retraceMsgQ);
    osStartThread(&_viLoopThread_0000935F);
    main_80000A94();
    func_800356EC();
    engine_8002B680();
    main_80001CFC();
    main_80000450();
    func_8000071C();
    func_80002494();
    gLoadMapNum = 0;

    do
    {
        if (D_800DEDE0)
        {
            if (D_800DEDE0 == 2)
                func_801C9B48();
            if (D_800DEDE0 == 3)
                func_801C9E7C();
            if (D_800DEDE0 == 4)
            {
                D_800BD3E8 = 0;
                main_80000610();
                D_800BD3F0_000BDFF0 = 0;
                func_801C9B48();
            }
            loadMap(gLoadMapNum);
            D_800DEDE0 = 0;
            D_801A1970 = 1;
        }

        D_80138788 = D_800FE9E0;
        D_800BD3E0_000BDFE0 += D_800FE9E0 - D_801AE498;
        D_801CE5D8 += D_800FE9E0 - D_801AE498;

        if (D_800BD3E0_000BDFE0 > 8LL)
            D_800BD3E0_000BDFE0 = 8LL;

        D_801AE498 = D_80138788;

        for (; D_800BD3E0_000BDFE0 > 2; D_800BD3E0_000BDFE0 -= 2)
            func_800017AC();

        if (D_800BD3E0_000BDFE0 >= 0)
        {
            func_800017AC();
            func_80001AF8();
            func_80000F00();

            D_800BD3E0_000BDFE0 -= 2;

            if (D_800BD3FC_000BDFFC != 0)
            {
                osRecvMesg(&D_8010A920, NULL, OS_MESG_BLOCK);
                D_800BD3FC_000BDFFC = 0;

                if (D_80119A5C != 0)
                    D_80119A5C--;

                if (_framebufferCount_000BDFD0 < 3)
                {
                    if (_retraceMsgQ.validCount >= _retraceMsgQ.msgCount)
                        osRecvMesg(&_retraceMsgQ, NULL, OS_MESG_BLOCK);

                    osRecvMesg(&_retraceMsgQ, NULL, OS_MESG_BLOCK);
                }
            }
            _createGfxTask();
            D_800BD3FC_000BDFFC = 1;
            D_800BD428_000BE028 = gGfxTaskIndex;
            gGfxTaskIndex ^= 1;
            _framebufferIndex_000BE020++;
            if (_framebufferIndex_000BE020 == _framebufferCount_000BDFD0)
                _framebufferIndex_000BE020 = 0;
        }
        yield_self();
    } while (1);
}
#endif