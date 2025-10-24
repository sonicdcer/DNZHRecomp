#include "patches.h"

extern Gfx* gpDisplayList;
extern s32 gScreenWidth;
extern s32 gScreenHeight;
extern s32 _framebufferIndex_000BE020;
extern u8* gDepthBuffer;
extern u8* _framebuffer[3];
extern s32 D_800BD3E8;
extern u8 _red_000BDFEC;
extern u8 _green_000BDFED;
extern u8 _blue_000BDFEE;
extern u16 gGraphicsOption;

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