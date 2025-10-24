#include "patches.h"

#if 1
/*800043F4*/
RECOMP_PATCH void scanSectors(s32 posx, s32 posy, s32 posz, f32 arg3, s16 sectnum) {
    f32 viewrange, f2, viewangle, viewangler2, viewangler1;
    s16 sectnum_;
    s32 i, j;

    D_8012FC40 = 1;
    
    // viewrange = (klabs(D_8016A15C) * 0.7999999999999999) /*(1/1.25)*/ + 0.6283185307179999 /*(PI/5)*/;
    // @recomp
    viewrange = DEG2RAD(90.f);

    if (sinf(D_801AC8E0) > 0.0f)
        f2 = sinf(D_801AC8E0);
    else
        f2 = -sinf(D_801AC8E0);

    if (cosf(D_801AC8E0) > 0.0f)
        viewrange *= (f2 + cosf(D_801AC8E0));
    else
        viewrange *= (f2 - cosf(D_801AC8E0));

    viewangle = angleModF((PI - arg3));
    _viewAngle = viewangle;
    _globalPosX = posx;
    _globalPosY = posy;
    _globalPosZ = posz;
    gDrawWallCnt = 0;
    gDrawCeilCnt = 0;
    gDrawFloorCnt = 0;
    _visWallCnt = 0;
    gVisibleSectorCnt = 0;
    viewangler2 = viewangle - viewrange;
    Bmemset(_visWalltBit, 0, sizeof(_visWalltBit));
    Bmemset(_wallBitCheck, 0, sizeof(_wallBitCheck));
    Bmemset(_floorBitCheck, 0, sizeof(_floorBitCheck));
    Bmemset(_ceilingBitCheck, 0, sizeof(_ceilingBitCheck));
    Bmemset(_visSectBit1, 0, sizeof(_visSectBit1));
    viewangler1 = viewangle + viewrange;

    scanSector(viewangler2, viewangler1, sectnum);

    for (i = 0; i < ((MAXWALLS + 7) >> 3); i++) {
        if (_visWalltBit[i] != 0) {
            for (j = 0; j < ARRAY_COUNT(_pow2char_000BE030) - 1; j++) {
                if (_visWalltBit[i] & _pow2char_000BE030[j]) {
                    gDrawWallList[gDrawWallCnt] = (i * 8) + j;
                    gDrawWallCnt++;
                }
            }
        }
    }

    for (i = 0; i < (((MAXSECTORS + 7) >> 3) - 1); i++) {
        if (_floorBitCheck[i] != 0) {
            for (j = 0; j < ARRAY_COUNT(_pow2char_000BE030) - 1; j++) {
                if (_floorBitCheck[i] & _pow2char_000BE030[j]) {
                    gDrawFloorList[gDrawFloorCnt] = (i * 8) + j;
                    gDrawFloorCnt++;
                }
            }
        }
    }

    for (i = 0; i < (((MAXSECTORS + 7) >> 3) - 1); i++) {
        if (_ceilingBitCheck[i] != 0) {
            for (j = 0; j < ARRAY_COUNT(_pow2char_000BE030) - 1; j++) {
                if (_ceilingBitCheck[i] & _pow2char_000BE030[j]) {
                    gDrawCeilingList[gDrawCeilCnt] = (i * 8) + j;
                    gDrawCeilCnt++;
                }
            }
        }
    }

    for (i = 0; i < (((MAXSECTORS + 7) >> 3) - 1); i++) {
        if (_visSectBit1[i] != 0) {
            for (j = 0; j < ARRAY_COUNT(_pow2char_000BE030) - 1; j++) {
                if (_visSectBit1[i] & _pow2char_000BE030[j]) {
                    sectnum_ = (i * 8) + j;
                    gVisibleSectors[gVisibleSectorCnt] = sectnum_;

                    if ((gpSector[sectnum_].ceilingstat & 1) || (gpSector[sectnum_].floorstat & 1))
                        D_8012FC40 = 0;

                    gVisibleSectorCnt++;
                }
            }
        }
    }

    gVisibleSectors[gVisibleSectorCnt] = -1;
    gDrawCeilingList[gDrawCeilCnt] = -1;
    gDrawFloorList[gDrawFloorCnt] = -1;
    gDrawWallList[gDrawWallCnt] = -1;
}
#endif

#if 1
RECOMP_PATCH s32 func_800115E0(ModelInfo* model) {
    Matrix4f mtx;
    Vec4f vec;
    Vec4f* ptr;
    f32 f;
    s32 i;

#if 0 // def TARGET_N64

    f = func_80011410(model);
    grMtxL2F(mtx, &gpDynamic->mtx3[D_801A6D80 - 1]);
    vec[0] = mtx[3][0] - gMapXpos * 0.5;
    vec[2] = -(mtx[3][1] - gMapYpos * 0.5);
    vec[1] = -(mtx[3][2] - gMapZpos * 0.5);

    for (i = 0, ptr = D_80197DF0; i < 4; i++, ptr++) {
        if (_dotProduct(*ptr, vec) < -f)
            return 0;
    }
#endif
    return 1;
}
#endif