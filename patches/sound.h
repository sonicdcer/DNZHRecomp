#ifndef __PATCH_AUDIO_H__
#define __PATCH_AUDIO_H__

#include "patch_helpers.h"

DECLARE_FUNC(float, recomp_get_bgm_volume);
DECLARE_FUNC(float, recomp_set_bgm_volume_100);
DECLARE_FUNC(float, recomp_set_bgm_volume_59);
DECLARE_FUNC(float, recomp_set_bgm_volume_0);
DECLARE_FUNC(float, recomp_get_sfx_volume);
DECLARE_FUNC(float, recomp_get_env_volume);
DECLARE_FUNC(u32, recomp_get_low_health_beeps_enabled);

#endif
