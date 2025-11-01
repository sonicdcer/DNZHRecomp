#include "patches.h"

#if DEBUG_MENU == 1
RECOMP_PATCH
void debugMenu(void) {
    char buffer[16];

    AlphaPalette* palette;
    Cloud* cloud;
    u8 i;
    u32 j;

    if (D_8012C470 == 4)
        return;

    if ((!gDebugMenu) && (gCheatWeatherConfig == 0))
        return;

    // _debugPlayerNum = (((D_8012C470) > 3) ? 3 : D_8012C470);
    // @recomp
    _debugPlayerNum = 0;

    if (gButton[_debugPlayerNum] & 0x1000) {
        if (!_screenSelectButtonPressed_000E0589) {
            _screenSelectButtonPressed_000E0589 = 1;
            _debugScreen_000E0588++;
        }
    } else {
        _screenSelectButtonPressed_000E0589 = 0;
    }

    if (gCheatWeatherConfig == 0) {
        _debugScreen_000E0588 &= 0xF;
    } else {
        if (_debugScreen_000E0588 == 9)
            _debugScreen_000E0588 = 0;

        if (_debugScreen_000E0588 != 0xFF) {
            _debugScreen_000E0588 %= 6;
            if (_debugScreen_000E0588 == 5)
                _debugScreen_000E0588 = 0xFF;
        }
    }
    switch (_debugScreen_000E0588) {
        case 0:
            if (gButton[_debugPlayerNum] & 0x8000)
                gFog[0].color[0].r = (((gFog[0].color[0].r + 1) > 255) ? 255 : gFog[0].color[0].r + 1);
            if (gButton[_debugPlayerNum] & 0x0004)
                gFog[0].color[0].g = (((gFog[0].color[0].g + 1) > 255) ? 255 : gFog[0].color[0].g + 1);
            if (gButton[_debugPlayerNum] & 0x0001)
                gFog[0].color[0].b = (((gFog[0].color[0].b + 1) > 255) ? 255 : gFog[0].color[0].b + 1);
            if (gButton[_debugPlayerNum] & 0x4000)
                gFog[0].color[0].r = (((gFog[0].color[0].r - 1) < 0) ? 0 : gFog[0].color[0].r - 1);
            if (gButton[_debugPlayerNum] & 0x0002)
                gFog[0].color[0].g = (((gFog[0].color[0].g - 1) < 0) ? 0 : gFog[0].color[0].g - 1);
            if (gButton[_debugPlayerNum] & 0x0008)
                gFog[0].color[0].b = (((gFog[0].color[0].b - 1) < 0) ? 0 : gFog[0].color[0].b - 1);
            if (gButton[_debugPlayerNum] & 0x0010)
                gFog[0].scale[0].fr = (((gFog[0].scale[0].fr + 1) > 3000) ? 3000 : gFog[0].scale[0].fr + 1);
            if (gButton[_debugPlayerNum] & 0x0100)
                gFog[0].scale[0].nr = (((gFog[0].scale[0].nr + 1) > 3000) ? 3000 : gFog[0].scale[0].nr + 1);
            if (gButton[_debugPlayerNum] & 0x0020)
                gFog[0].scale[0].fr = (((gFog[0].scale[0].fr - 1) < 0) ? 0 : gFog[0].scale[0].fr - 1);
            if (gButton[_debugPlayerNum] & 0x0200)
                gFog[0].scale[0].nr = (((gFog[0].scale[0].nr - 1) < 0) ? 0 : gFog[0].scale[0].nr - 1);

            gFog[0].scale[0].fr =
                ((gFog[0].scale[0].fr) > (gFog[0].scale[0].nr + 3) ? (gFog[0].scale[0].fr) : (gFog[0].scale[0].nr + 3));
            gFog[0].scale[1].nr = gFog[0].scale[0].nr;
            gFog[0].scale[1].fr = gFog[0].scale[0].fr;
            gFog[0].unk1E = 0;
            gFog[0].color[1].r = gFog[0].color[0].r;
            gFog[0].color[1].g = gFog[0].color[0].g;
            gFog[0].color[1].b = gFog[0].color[0].b;

            drawDebugString(25, 20, "FOG");
            sprintf(buffer, "R %d", gFog[0].color[0].r);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "G %d", gFog[0].color[0].g);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "B %d", gFog[0].color[0].b);
            drawDebugString(25, 50, buffer);
            sprintf(buffer, "NR %d", gFog[0].scale[0].nr);
            drawDebugString(25, 60, buffer);
            sprintf(buffer, "FR %d", gFog[0].scale[0].fr);
            drawDebugString(25, 70, buffer);
            break;
        case 1:
            if (gButton[_debugPlayerNum] & 0x8000)
                gSkyTopR = (((gSkyTopR + 1) > 255) ? 255 : gSkyTopR + 1);
            if (gButton[_debugPlayerNum] & 0x0004)
                gSkyTopG = (((gSkyTopG + 1) > 255) ? 255 : gSkyTopG + 1);
            if (gButton[_debugPlayerNum] & 0x0001)
                gSkyTopB = (((gSkyTopB + 1) > 255) ? 255 : gSkyTopB + 1);
            if (gButton[_debugPlayerNum] & 0x4000)
                gSkyTopR = (((gSkyTopR - 1) < 0) ? 0 : gSkyTopR - 1);
            if (gButton[_debugPlayerNum] & 0x0002)
                gSkyTopG = (((gSkyTopG - 1) < 0) ? 0 : gSkyTopG - 1);
            if (gButton[_debugPlayerNum] & 0x0008)
                gSkyTopB = (((gSkyTopB - 1) < 0) ? 0 : gSkyTopB - 1);

            drawDebugString(25, 20, "SKY TOP");
            sprintf(buffer, "R %d", gSkyTopR);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "G %d", gSkyTopG);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "B %d", gSkyTopB);
            drawDebugString(25, 50, buffer);
            break;
        case 2:
            if (gButton[_debugPlayerNum] & 0x8000)
                gSkyBottomR = (((gSkyBottomR + 1) > 255) ? 255 : gSkyBottomR + 1);
            if (gButton[_debugPlayerNum] & 0x0004)
                gSkyBottomG = (((gSkyBottomG + 1) > 255) ? 255 : gSkyBottomG + 1);
            if (gButton[_debugPlayerNum] & 0x0001)
                gSkyBottomB = (((gSkyBottomB + 1) > 255) ? 255 : gSkyBottomB + 1);
            if (gButton[_debugPlayerNum] & 0x4000)
                gSkyBottomR = (((gSkyBottomR - 1) < 0) ? 0 : gSkyBottomR - 1);
            if (gButton[_debugPlayerNum] & 0x0002)
                gSkyBottomG = (((gSkyBottomG - 1) < 0) ? 0 : gSkyBottomG - 1);
            if (gButton[_debugPlayerNum] & 0x0008)
                gSkyBottomB = (((gSkyBottomB - 1) < 0) ? 0 : gSkyBottomB - 1);

            drawDebugString(25, 20, "SKY BOTTOM");
            sprintf(buffer, "R %d", gSkyBottomR);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "G %d", gSkyBottomG);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "B %d", gSkyBottomB);
            drawDebugString(25, 50, buffer);
            break;
        case 3:
        case 4:
            i = _debugScreen_000E0588 - 3;
            cloud = &gCloud[i];
            if (gButton[_debugPlayerNum] & 0x8000)
                cloud->fog.r = (((cloud->fog.r + 1) > 255) ? 255 : cloud->fog.r + 1);
            if (gButton[_debugPlayerNum] & 0x0004)
                cloud->fog.g = (((cloud->fog.g + 1) > 255) ? 255 : cloud->fog.g + 1);
            if (gButton[_debugPlayerNum] & 0x0001)
                cloud->fog.b = (((cloud->fog.b + 1) > 255) ? 255 : cloud->fog.b + 1);
            if (gButton[_debugPlayerNum] & 0x4000)
                cloud->fog.r = (((cloud->fog.r - 1) < 0) ? 0 : cloud->fog.r - 1);
            if (gButton[_debugPlayerNum] & 0x0002)
                cloud->fog.g = (((cloud->fog.g - 1) < 0) ? 0 : cloud->fog.g - 1);
            if (gButton[_debugPlayerNum] & 0x0008)
                cloud->fog.b = (((cloud->fog.b - 1) < 0) ? 0 : cloud->fog.b - 1);
            if (gButton[_debugPlayerNum] & 0x0010)
                cloud->height += 300;
            if (gButton[_debugPlayerNum] & 0x0020)
                cloud->height -= 300;
            if (gButton[_debugPlayerNum] & 0x0100)
                gCloudSpeed[i] = (((gCloudSpeed[i] + 1) > 1023) ? 1023 : gCloudSpeed[i] + 1);
            if (gButton[_debugPlayerNum] & 0x0200)
                gCloudSpeed[i] = (((gCloudSpeed[i] - 1) < 0) ? 0 : gCloudSpeed[i] - 1);
            if (gButton[_debugPlayerNum] & 0x0800)
                gCloudAng[i] = (gCloudAng[i] + 4) & 0x7FF;
            if (gButton[_debugPlayerNum] & 0x0400)
                gCloudAng[i] = (gCloudAng[i] - 4) & 0x7FF;

            cloud->unk8 = (-cosf((gCloudAng[i] * (3.14159265359 / 1024))) * gCloudSpeed[i]) / 50.0f;
            cloud->unkC = (-sinf((gCloudAng[i] * (3.14159265359 / 1024))) * gCloudSpeed[i]) / 50.0f;

            sprintf(buffer, "CLOUDS %d", i + 1);
            drawDebugString(25, 20, buffer);
            sprintf(buffer, "R %d", cloud->fog.r);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "G %d", cloud->fog.g);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "B %d", cloud->fog.b);
            drawDebugString(25, 50, buffer);
            sprintf(buffer, "HT %d", cloud->height / 10);
            drawDebugString(25, 60, buffer);
            sprintf(buffer, "AN %d", gCloudAng[i]);
            drawDebugString(25, 70, buffer);
            sprintf(buffer, "SP %d", gCloudSpeed[i]);
            drawDebugString(25, 80, buffer);
            break;
        case 5:
            drawDebugString(25, 20, "PLAYER");
            sprintf(buffer, "XV %d", gPlayer[0].xvect);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "YV %d", gPlayer[0].yvect);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "ZV %d", gPlayer[0].zvect);
            drawDebugString(25, 50, buffer);
            sprintf(buffer, "OF %d", gPlayer[0].unk59);
            drawDebugString(25, 60, buffer);
            sprintf(buffer, "OW %d", gPlayer[0].unk56);
            drawDebugString(25, 70, buffer);
            sprintf(buffer, "JF %d", gPlayer[0].unk44);
            drawDebugString(25, 80, buffer);
            sprintf(buffer, "DN %d", gPlayer[0].skin);
            drawDebugString(25, 90, buffer);

            if (!_cmdButtonPressed_000E058A) {
                if (gButton[_debugPlayerNum] & 0x0020) {
                    gPlayer[0].skin--;
                    if (gPlayer[0].skin < 0)
                        gPlayer[0].skin = D_80138780 - 1;
                    _cmdButtonPressed_000E058A = 1;
                    gpSprite[gPlayer[0].unk4A].picnum = D_8012F6E4[gPlayer[0].skin].picnum;
                }
                if (gButton[_debugPlayerNum] & 0x0010) {
                    gPlayer[0].skin++;
                    if (gPlayer[0].skin >= D_80138780)
                        gPlayer[0].skin = 0;
                    _cmdButtonPressed_000E058A = 1;
                    gpSprite[gPlayer[0].unk4A].picnum = D_8012F6E4[gPlayer[0].skin].picnum;
                }
            } else if ((gButton[_debugPlayerNum] & (0x0020 | 0x0010)) == 0) {
                _cmdButtonPressed_000E058A = 0;
            }

            break;
        case 6:
            drawDebugString(25, 20, "GFX");
            sprintf(buffer, "GLIST %d - %d", gDisplayListSize, gDisplayListMaxSize);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "VLIST %d - %d", gVertexN64Size, gVertexN64MaxSize);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "GFX TIME %d", gGfxTime);
            drawDebugString(25, 50, buffer);
            j = func_80040C08(3);
            sprintf(buffer, "DRAW TIME %d", j);
            drawDebugString(25, 60, buffer);
            j = func_80040C08(1);
            sprintf(buffer, "MOVE1 TIME %d", j);
            drawDebugString(25, 70, buffer);
            j = func_80040C08(2);
            sprintf(buffer, "MOVE2 TIME %d", j);
            drawDebugString(25, 80, buffer);
            sprintf(buffer, "CACHE %d/%d", getRemainingCacheSize(), gCacheNum);
            drawDebugString(25, 0x5A, buffer);
            sprintf(buffer, "LIST %d%%", getDisplayListVertexUsagePercentage());
            drawDebugString(25, 0x64, buffer);
            break;
        case 7:
            drawDebugString(25, 20, "AI");
            sprintf(buffer, "Ai: %d", gDisableAI);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "Alert Aliens: %d", gAlertAliens);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "Snoozing Aliens: %d", gSnoozingAliens);
            drawDebugString(25, 50, buffer);
            sprintf(buffer, "AutoAim: %d", gAutoAim);
            drawDebugString(25, 60, buffer);
            sprintf(buffer, "Difficulty (0=E, 1=M, 2=H) : %d", gConfig.difficulty);
            drawDebugString(25, 70, buffer);
            sprintf(buffer, "Invul: %d", gInvulnerability);
            drawDebugString(25, 80, buffer);

            if ((!_cmdButtonPressed_000E058A)) {
                if (gButton[_debugPlayerNum] & 0x8000) {
                    _cmdButtonPressed_000E058A = 1;
                    gDisableAI ^= 1;
                }
            }
            if ((!_cmdButtonPressed_000E058A)) {
                if (gButton[_debugPlayerNum] & 0x0020) {
                    gConfig.difficulty++;
                    if (gConfig.difficulty >= 3)
                        gConfig.difficulty = 0;
                    func_80050408();
                    _cmdButtonPressed_000E058A = 1;
                }
            }
            if ((!_cmdButtonPressed_000E058A)) {
                if (gButton[_debugPlayerNum] & 0x0010) {
                    _cmdButtonPressed_000E058A = 1;
                    gAutoAim ^= 1;
                }
                break;
            } else if ((gButton[_debugPlayerNum] & (0x8000 | 0x4000 | 0x0020 | 0x0010)) == 0) {
                _cmdButtonPressed_000E058A = 0;
            }
            break;
        case 8:
            palette = gpAlphaPalette;
            if (gButton[_debugPlayerNum] & 0x8000)
                palette->primary.r = (((palette->primary.r + 1) > 255) ? 255 : palette->primary.r + 1);
            if (gButton[_debugPlayerNum] & 0x0004)
                palette->primary.g = (((palette->primary.g + 1) > 255) ? 255 : palette->primary.g + 1);
            if (gButton[_debugPlayerNum] & 0x0001)
                palette->primary.b = (((palette->primary.b + 1) > 255) ? 255 : palette->primary.b + 1);
            if (gButton[_debugPlayerNum] & 0x4000)
                palette->primary.r = (((palette->primary.r - 1) < 0) ? 0 : palette->primary.r - 1);
            if (gButton[_debugPlayerNum] & 0x0002)
                palette->primary.g = (((palette->primary.g - 1) < 0) ? 0 : palette->primary.g - 1);
            if (gButton[_debugPlayerNum] & 0x0008)
                palette->primary.b = (((palette->primary.b - 1) < 0) ? 0 : palette->primary.b - 1);
            if (gButton[_debugPlayerNum] & 0x0010)
                palette->env.r = (((palette->env.r + 1) > 255) ? 255 : palette->env.r + 1);
            if (gButton[_debugPlayerNum] & 0x0100)
                palette->env.g = (((palette->env.g + 1) > 255) ? 255 : palette->env.g + 1);
            if (gButton[_debugPlayerNum] & 0x0800)
                palette->env.b = (((palette->env.b + 1) > 255) ? 255 : palette->env.b + 1);
            if (gButton[_debugPlayerNum] & 0x0020)
                palette->env.r = (((palette->env.r - 1) < 0) ? 0 : palette->env.r - 1);
            if (gButton[_debugPlayerNum] & 0x0200)
                palette->env.g = (((palette->env.g - 1) < 0) ? 0 : palette->env.g - 1);
            if (gButton[_debugPlayerNum] & 0x0400)
                palette->env.b = (((palette->env.b - 1) < 0) ? 0 : palette->env.b - 1);

            drawDebugString(25, 20, "ALPHA PALETTE");
            sprintf(buffer, "R0 %d", palette->primary.r);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "G0 %d", palette->primary.g);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "B0 %d", palette->primary.b);
            drawDebugString(25, 50, buffer);
            sprintf(buffer, "R1 %d", palette->env.r);
            drawDebugString(25, 60, buffer);
            sprintf(buffer, "G1 %d", palette->env.g);
            drawDebugString(25, 70, buffer);
            sprintf(buffer, "B1 %d", palette->env.b);
            drawDebugString(25, 80, buffer);
            break;
        case 9:
            drawDebugString(25, 20, "SFX");
            sprintf(buffer, "FX %d", _sfxnum_000E0556);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "KILLS %d:%d", D_801A1958.enemies_killed, D_801A1958.enemies_total);
            drawDebugString(25, 40, buffer);

            if (!_cmdButtonPressed_000E058A) {
                if (gButton[_debugPlayerNum] & 0x8000) {
                    _cmdButtonPressed_000E058A = 1;
                    gPlayer[0].third_person = 1;
                    gPlayer[0].unk64 = 0;
                }
                if (gButton[_debugPlayerNum] & 0x4000) {
                    _cmdButtonPressed_000E058A = 1;
                    gPlayer[0].third_person = 0;
                    gPlayer[0].unk64 = 0;
                }
                if (gButton[_debugPlayerNum] & 0x0010) {
                    _cmdButtonPressed_000E058A = 1;
                    _sfxnum_000E0556 = (((_sfxnum_000E0556 + 1) > 2000) ? 2000 : _sfxnum_000E0556 + 1);
                }
                if (gButton[_debugPlayerNum] & 0x0020) {
                    _cmdButtonPressed_000E058A = 1;
                    _sfxnum_000E0556 = (((_sfxnum_000E0556 - 1) < 1) ? 1 : _sfxnum_000E0556 - 1);
                }
                if (gButton[_debugPlayerNum] & 0x0100) {
                    _cmdButtonPressed_000E058A = 1;
                    _sfxnum_000E0556 = (((_sfxnum_000E0556 + 10) > 2000) ? 2000 : _sfxnum_000E0556 + 10);
                }
                if (gButton[_debugPlayerNum] & 0x0200) {
                    _cmdButtonPressed_000E058A = 1;
                    _sfxnum_000E0556 = (((_sfxnum_000E0556 - 10) < 1) ? 1 : _sfxnum_000E0556 - 10);
                }
                if (gButton[_debugPlayerNum] & 0x2000) {
                    _cmdButtonPressed_000E058A = 1;
                    MusHandleStop(_mushandle_000E0558, 0);
                    _mushandle_000E0558 = MusStartEffect(_sfxnum_000E0556);
                }
            } else if ((gButton[_debugPlayerNum] & (0x8000 | 0x4000 | 0x2000 | 0x0020 | 0x0010)) == 0) {
                _cmdButtonPressed_000E058A = 0;
            }
            break;
        case 10:
            drawDebugString(25, 20, "LEVEL WARP");
            j = gMapChapter[gLoadMapNum].chapter;
            drawDebugString(25, 30, _chapterName_000E055C[j]);
            drawDebugString(25, 40, gMapChapter[gLoadMapNum].mapname);

            if (!_cmdButtonPressed_000E058A) {
                if (gButton[_debugPlayerNum] & 0x4000) {
                    func_8008E01C(30, 1);
                    break;
                }
                if (gButton[_debugPlayerNum] & 0x0020) {
                    _cmdButtonPressed_000E058A = 1;
                    gLoadMapNum--;
                    if (gLoadMapNum < 0)
                        for (gLoadMapNum = 0; gMapChapter[gLoadMapNum + 1].chapter != 99; gLoadMapNum++)
                            ;
                }
                if (gButton[_debugPlayerNum] & 0x0010) {
                    _cmdButtonPressed_000E058A = 1;
                    gLoadMapNum++;
                    if (gMapChapter[gLoadMapNum].chapter == 99)
                        gLoadMapNum = 0;
                }
                if (gButton[_debugPlayerNum] & 0x2000) {
                    _cmdButtonPressed_000E058A = 1;
                    func_8008E01C(30, 2);
                    break;
                }
            } else if ((gButton[_debugPlayerNum] & (0x8000 | 0x2000 | 0x0020 | 0x0010)) == 0) {
                _cmdButtonPressed_000E058A = 0;
            }
            break;
        case 11:
            drawDebugString(25, 20, "MIDI");

            if (!_playAmbient_000E0554)
                sprintf(buffer, "TUNE %d", _musicnum_000E0552);
            else
                sprintf(buffer, "AMBIENT %d", _musicnum_000E0552);

            drawDebugString(25, 30, buffer);
            sprintf(buffer, "CHANNELS %d", MusAsk(3));
            drawDebugString(25, 40, buffer);

            if (!_cmdButtonPressed_000E058A) {
                if (gButton[_debugPlayerNum] & 0x8000) {
                    _cmdButtonPressed_000E058A = 1;
                    if (!_playAmbient_000E0554)
                        playMusic(_musicnum_000E0552);
                    else
                        playAmbient(_musicnum_000E0552);
                }
                if (gButton[_debugPlayerNum] & 0x4000) {
                    _cmdButtonPressed_000E058A = 1;
                    MusStop(2, 0);
                }
                if (gButton[_debugPlayerNum] & 0x0010) {
                    _cmdButtonPressed_000E058A = 1;
                    if (!_playAmbient_000E0554)
                        _musicnum_000E0552 = (((_musicnum_000E0552 + 1) > 12 - 1) ? 12 - 1 : _musicnum_000E0552 + 1);
                    else
                        _musicnum_000E0552 = (((_musicnum_000E0552 + 1) > 9 - 1) ? 9 - 1 : _musicnum_000E0552 + 1);
                }
                if (gButton[_debugPlayerNum] & 0x0020) {
                    _cmdButtonPressed_000E058A = 1;
                    _musicnum_000E0552 = (((_musicnum_000E0552 - 1) < 0) ? 0 : _musicnum_000E0552 - 1);
                }
                if (gButton[_debugPlayerNum] & 0x2000) {
                    _cmdButtonPressed_000E058A = 1;
                    _playAmbient_000E0554 = !_playAmbient_000E0554;
                }
            } else if ((gButton[_debugPlayerNum] & (0x8000 | 0x4000 | 0x2000 | 0x0020 | 0x0010)) == 0) {
                _cmdButtonPressed_000E058A = 0;
            }
            break;
        case 12:
            if (gButton[_debugPlayerNum] & 0x8000)
                gpGlobalPalette->r = (((gpGlobalPalette->r + 1) > 256) ? 256 : gpGlobalPalette->r + 1);
            if (gButton[_debugPlayerNum] & 0x0004)
                gpGlobalPalette->g = (((gpGlobalPalette->g + 1) > 256) ? 256 : gpGlobalPalette->g + 1);
            if (gButton[_debugPlayerNum] & 0x0001)
                gpGlobalPalette->b = (((gpGlobalPalette->b + 1) > 256) ? 256 : gpGlobalPalette->b + 1);
            if (gButton[_debugPlayerNum] & 0x4000)
                gpGlobalPalette->r = (((gpGlobalPalette->r - 1) < 0) ? 0 : gpGlobalPalette->r - 1);
            if (gButton[_debugPlayerNum] & 0x0002)
                gpGlobalPalette->g = (((gpGlobalPalette->g - 1) < 0) ? 0 : gpGlobalPalette->g - 1);
            if (gButton[_debugPlayerNum] & 0x0008)
                gpGlobalPalette->b = (((gpGlobalPalette->b - 1) < 0) ? 0 : gpGlobalPalette->b - 1);

            drawDebugString(25, 20, "GLOBAL PALETTE");
            sprintf(buffer, "R %d", gpGlobalPalette->r);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "G %d", gpGlobalPalette->g);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "B %d", gpGlobalPalette->b);
            drawDebugString(25, 50, buffer);
            break;
        case 13:
            drawDebugString(25, 20, "CHEAT");
            drawDebugString(25, 30, "Z FOR ALL WEAPONS");
            drawDebugString(25, 40, "L FOR ALL ITEMS");
            drawDebugString(25, 50, "R FOR ALL KEYS");
            drawDebugString(25, 60, "A FOR INVUL");

            if (gButton[_debugPlayerNum] & 0x2000) {
                for (j = 0; j < 50; j++) {
                    if (j - 31 < 2 || j == 30)
                        continue;
                    else if (j == 33 || j == 0)
                        continue;
                    else if (j == 0 || j == 19)
                        continue;
                    else if (j == 22 || j == 1)
                        continue;
                    else if (j < (s32) (sizeof(D_8011A680[0]) / sizeof(D_8011A680[0][0]))) {
                        D_8011A680[0][j][0] |= 1;
                        D_8011A680[0][j][1] = 999;
                    }
                }
            }

            if (gButton[_debugPlayerNum] & 0x0020) {
                gActor[gActorSpriteMap[gPlayer[0].unk4A]].unk7E = 100;
                for (j = 0; j < (s32) (sizeof(D_8010A940[0].unkA) / sizeof(D_8010A940[0].unkA[0])); j++)
                    D_8010A940[0].unkA[j] = D_800E17E0[j];
            }
            if (gButton[_debugPlayerNum] & 0x0010) {
                for (j = 1; j < (s32) (sizeof(gPlayer[0].keys) / sizeof(gPlayer[0].keys[0])); j++)
                    gPlayer[0].keys[j] = 1;
            }
            if (gButton[_debugPlayerNum] & 0x8000) {
                if (!_cmdButtonPressed_000E058A) {
                    audio_80008574(0, 945);
                    gInvulnerability ^= 1;
                    if (gInvulnerability != 0)
                        gActor[gActorSpriteMap[gPlayer[0].unk4A]].unk8 = 999;
                    else
                        gActor[gActorSpriteMap[gPlayer[0].unk4A]].unk8 = gPlayer[0].unk48;
                    _cmdButtonPressed_000E058A = 1;
                }
            } else {
                _cmdButtonPressed_000E058A = 0;
            }
            break;
        case 14:
            drawDebugString(25, 20, "AI Debug values");
            sprintf(buffer, "Gvar 1 %d", gAiDebugGvar1);
            drawDebugString(25, 30, buffer);
            sprintf(buffer, "Gvar 2 %d", gAiDebugGvar2);
            drawDebugString(25, 40, buffer);
            sprintf(buffer, "Gvar 3 %d", gAiDebugGvar3);
            drawDebugString(25, 50, buffer);

            if (!_cmdButtonPressed_000E058A) {
                if (gButton[_debugPlayerNum] & 0x8000) {
                    _cmdButtonPressed_000E058A = 1;
                    if (gButton[_debugPlayerNum] & 0x0020)
                        gAiDebugGvar1 += 10;
                    else
                        gAiDebugGvar1++;
                }
                if (gButton[_debugPlayerNum] & 0x0004) {
                    _cmdButtonPressed_000E058A = 1;
                    if (gButton[_debugPlayerNum] & 0x0020)
                        gAiDebugGvar2 += 10;
                    else
                        gAiDebugGvar2++;
                }
                if (gButton[_debugPlayerNum] & 0x0001) {
                    _cmdButtonPressed_000E058A = 1;
                    if (gButton[_debugPlayerNum] & 0x0020)
                        gAiDebugGvar3 += 10;
                    else
                        gAiDebugGvar3++;
                }
                if (gButton[_debugPlayerNum] & 0x4000) {
                    _cmdButtonPressed_000E058A = 1;
                    if (gButton[_debugPlayerNum] & 0x0020)
                        gAiDebugGvar1 -= 10;
                    else
                        gAiDebugGvar1--;
                }
                if (gButton[_debugPlayerNum] & 0x0002) {
                    _cmdButtonPressed_000E058A = 1;
                    if (gButton[_debugPlayerNum] & 0x0020)
                        gAiDebugGvar2 -= 10;
                    else
                        gAiDebugGvar2--;
                }
                if (gButton[_debugPlayerNum] & 0x0008) {
                    _cmdButtonPressed_000E058A = 1;
                    if (gButton[_debugPlayerNum] & 0x0020)
                        gAiDebugGvar3 -= 10;
                    else
                        gAiDebugGvar3--;
                }
            } else if ((gButton[_debugPlayerNum] & (0x8000 | 0x4000 | 0x0008 | 0x0002 | 0x0001 | 0x0004)) == 0) {
                _cmdButtonPressed_000E058A = 0;
            }
            break;
    }
}
#endif

#if DEBUG_SKIP_INTRO == 1
RECOMP_PATCH void func_800006B4(void) {
    s32 i;
    if (controller_8008AEF0()) {
        for (i = 0; i < ARRAY_COUNT(D_8016D174); i++) {
            if (D_8016D174[i] == 0)
                break;
        }

        D_801CC8CA = i;
        // @recomp
        // main_80000624(&func_801C6560);
    }
}
#endif

#if DEBUG_SKIP_INTRO == 1
RECOMP_PATCH
void func_801C15CC(void) {
    s32 i;

    // @recomp
    D_800BD3F8 = 1;

    D_801CE5D8 = 0x25252525;
    allocMemory(320, 240 * 2, 0x1400 * 2, 0);
    setCameraPosition(0.0f, 0.0f, -500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    func_801C10C8();
    func_8007FD8C(&D_800DFA40[0], 0);
    D_801CDA94 = D_8010A938;
    func_8007FD8C(&D_800DFB08[0], 11);
    func_8007FD8C(&D_800E0778[0], 5);
    D_801CDA20 = func_8007FC08(&D_800DFA40[0], 0, 0, 0, 500);
    edl_80081688(&D_801CF638, 16);
    edl_80081688(&D_801CC91C, 17);
    edl_80081688(&D_801CC920, 19);
    edl_80081688(&D_801CDB1C, 18);
    D_801CF70C = func_8008372C(0, &D_801CA310_000F4890[1], 0x9080, &D_801CA3B8_000F4938, 0);
    D_801CF62C = D_801ACBD4;
    gSPTexture(D_801ACBD4, 0x05BC, 0x05BC, 0, G_TX_RENDERTILE, G_ON);
    D_801CC890 = func_8008372C(0, &D_801CA310_000F4890[2], 0, &D_801CA3B8_000F4938, 0);
    D_801CC890->unk64 -= 30.0f;
    func_801C14B4(D_801CC890, 0, 0, 0xFF);
    D_801CF70C->unk3C = -1920.0f;
    D_801CDBFC = func_8008372C(0, &D_801CA310_000F4890[3], 0x9080, &D_801CA3B8_000F4938, 0);
    D_801CDBFC->unk12 = 80;
    D_801CDBFC->unk3C = 400.0f;
    func_801C14B4(D_801CDBFC, 0, 0, 0xFF);
    D_801CDB04 = 0;
    D_801CF630 = 0xFF;

    for (i = 0; i < (s32) (sizeof(D_801CA360_000F48E0) / sizeof(D_801CA360_000F48E0[0])); i++)
        func_80083700(0, &D_801CA360_000F48E0[i], 0, 0);

    for (i = 0; i < (s32) (sizeof(D_801CA388_000F4908) / sizeof(D_801CA388_000F4908[0])); i++)
        func_80083700(0, &D_801CA388_000F4908[i], 0x1000, 0);

    func_80083700(0, &D_801CA310_000F4890[0], 128, 0);
    main_80002390();
    main_80000610();
    func_801C1114();
    func_801C1158(0, 0, 0, 0xFF);
    D_801CC88C = -1;
    func_801C73A0();
    D_801CF640 = 0;
    D_801CC918 = 0;
    playSfx(1059);

    if ((gMusicHandle == 0) || (MusHandleAsk(gMusicHandle) == 0) || (gMusicNum != 2))
        playMusic(2);

    D_800BD3F9 = 1;
    D_801CD974 = 0;
}
#endif

// Controller pak debugging patch function
#if 1
/*8008A724*/
RECOMP_PATCH
void controller_8008A724(void) {
    s32 i;

    if (D_800FA2F6_0000FBF5 != 0) {
        osRecvMesg(&_serialMsgQ_0000F60F, NULL, 1);
        osContGetReadData(D_800F9D40_0000F63F);

        for (i = 0; i < MAXPLAYERS; i++) {
            gController[i].stick_x = D_800F9D40_0000F63F[i].stick_x;
            gController[i].stick_y = D_800F9D40_0000F63F[i].stick_y;

            if ((D_800F9EF8_0000F7F7[i] != 0) || (D_800F9EFC_0000F7FB != 0)) {
                if (gController[i].stick_x < -30)
                    D_800F9D40_0000F63F[i].button |= L_JPAD;

                if (gController[i].stick_x > 30)
                    D_800F9D40_0000F63F[i].button |= R_JPAD;

                if (gController[i].stick_y < -31)
                    D_800F9D40_0000F63F[i].button |= D_JPAD;

                if (gController[i].stick_y > 31)
                    D_800F9D40_0000F63F[i].button |= U_JPAD;
            }

            if ((D_800F9D40_0000F63F[i].button & (L_JPAD | R_JPAD)) == (L_JPAD | R_JPAD))
                D_800F9D40_0000F63F[i].button ^= (L_JPAD | R_JPAD);

            if ((D_800F9D40_0000F63F[i].button & (D_JPAD | U_JPAD)) == (D_JPAD | U_JPAD))
                D_800F9D40_0000F63F[i].button ^= (D_JPAD | U_JPAD);

            gController[i].button2 =
                D_800F9D40_0000F63F[i].button & (gController[i].button ^ D_800F9D40_0000F63F[i].button);
            gController[i].button = D_800F9D40_0000F63F[i].button;

            if (D_80197D44[i] != 0) {
                if (D_800FA2EE_0000FBED[i] != 0)
                    D_800FA2EE_0000FBED[i]--;

                if (D_800FA2CA_0000FBC9[i] == 0) {
                    if (D_8019956D[i] & 2)
                        func_80087B9C(i);
                } else {
                    D_800FA2E6_0000FBE5[i]++;
                    if (D_800FA2E6_0000FBE5[i] >= 600) {
                        func_8008A59C(i);
                        D_800FA2EE_0000FBED[i] = 60;
                    } else {
                        D_800FA2CA_0000FBC9[i]--;
                        D_800FA2DA_0000FBD9[i] -= D_800FA2E2_0000FBE1[i];
                        if (D_800FA2DA_0000FBD9[i] < 0) {
                            D_800FA2DA_0000FBD9[i] += 256;
                            if (!(D_8019956D[i] & 1))
                                func_80087A90(i);
                        } else {
                            if (D_8019956D[i] & 1)
                                func_80087B00(i);
                        }
                    }
                }
            }
        }

        switch (D_80119A70) {
            case CONTROLLER_EEPROM_LONG_READ:
                osEepromLongRead(&_serialMsgQ_0000F60F, _arg0_0000FBFF, (u8*) _arg1_0000FC03, _arg2_0000FC07);
                break;
            case CONTROLLER_EEPROM_LONG_WRITE:
                osEepromLongWrite(&_serialMsgQ_0000F60F, _arg0_0000FBFF, (u8*) _arg1_0000FC03, _arg2_0000FC07);
                break;
            case CONTROLLER_PFS_NUM_FILES:
                D_800FE408 = osPfsNumFiles((OSPfs*) _arg0_0000FBFF, (s32*) _arg1_0000FC03, (s32*) _arg2_0000FC07);
                break;
            case CONTROLLER_PFS_FREE_BLOCKS:
                D_800FE408 = osPfsFreeBlocks((OSPfs*) _arg0_0000FBFF, (s32*) _arg1_0000FC03);
                break;
            case CONTROLLER_PFS_FILE_STATE:
                D_800FE408 = osPfsFileState((OSPfs*) _arg0_0000FBFF, _arg1_0000FC03, (OSPfsState*) _arg2_0000FC07);
                break;
            case CONTROLLER_PFS_DELETE_FILE:
                D_800FE408 = osPfsDeleteFile((OSPfs*) _arg0_0000FBFF, _arg1_0000FC03, (u32) _arg2_0000FC07,
                                             (u8*) _arg3_0000FC0B, (u8*) _arg4_0000FC0F);
#if 1
                u8* ext_name = (u8*) _arg4_0000FC0F;
                u8* game_name = (u8*) _arg3_0000FC0B;
                // @recomp: debug
                recomp_printf("callback osPfsDeleteFile from game:\n \
                            company_code: %x \n \
                            game_code: %x \n",
                              _arg1_0000FC03, _arg2_0000FC07);
                
                recomp_printf("ext_name: ");
                for (int i = 0; i < 4; i++) {
                    recomp_printf("%x",(u8*) ext_name[i]);
                }
                recomp_printf("\n");

                recomp_printf("game_name: ");
                for (size_t i = 0; i < 16; i++) {
                    recomp_printf("%x", game_name[i]);
                }
                recomp_printf("\n");
#endif
                break;
            case CONTROLLER_PFS_INIT_PAK:
                D_800FE408 = osPfsInitPak(&_serialMsgQ_0000F60F, (OSPfs*) _arg0_0000FBFF, _arg1_0000FC03);
                break;
            case CONTROLLER_PFS_REPAIR_ID:
                D_800FE408 = osPfsRepairId((OSPfs*) _arg0_0000FBFF);
                break;
            case CONTROLLER_PFS_READ_WRITE_FILE:
                D_800FE408 = osPfsReadWriteFile((OSPfs*) _arg0_0000FBFF, _arg1_0000FC03, _arg2_0000FC07, _arg3_0000FC0B,
                                                _arg4_0000FC0F, (u8*) _arg5_0000FC13);
                break;
            case CONTROLLER_PFS_ALLOCATE_FILE:
                D_800FE408 = osPfsAllocateFile((OSPfs*) _arg0_0000FBFF, _arg1_0000FC03, (u32) _arg2_0000FC07,
                                               (u8*) _arg3_0000FC0B, (u8*) _arg4_0000FC0F, (s32) _arg5_0000FC13,
                                               (s32*) _arg6_0000FC17);
                break;
            case CONTROLLER_PFS_FIND_FILE:
                D_800FE408 = osPfsFindFile((OSPfs*) _arg0_0000FBFF, _arg1_0000FC03, (u32) _arg2_0000FC07,
                                           (u8*) _arg3_0000FC0B, (u8*) _arg4_0000FC0F, (s32*) _arg5_0000FC13);
                break;
            case CONTROLLER_MOTOR_INIT:
                // @force unplugged Rumble Pak.
                // D_800FE408 = osMotorInit(&_serialMsgQ_0000F60F, (OSPfs*) _arg0_0000FBFF, _arg1_0000FC03);
                D_800FE408 = 1;
                break;
            case CONTROLLER_GET_STATUS:
                D_800FE408 = osContStartQuery(&_serialMsgQ_0000F60F);
                osRecvMesg(&_serialMsgQ_0000F60F, NULL, 1);
                osContGetQuery(_statusData_0000F62F);
                break;
        }
        D_80119A70 = 0;
        osContStartReadData(&_serialMsgQ_0000F60F);
    }
}
#endif

#if 0
RECOMP_PATCH
u8 func_8008A370(u8 pfsCmd, s32 contAddr, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    if (D_80119A70 == 0) {
        // @recomp: debug
        recomp_printf("Calling func_8008A370:\n \
                            company_code: %x \n \
                            game_code: %x \n \
                            game_name: %x \n \
                            ext_name: %x \n \
                            file_size_in_bytes: %x \n \
                            file_no: %x \n",
                      arg2, arg3, arg4, arg5, arg6, arg7);
        _arg0_0000FBFF = contAddr;
        _arg1_0000FC03 = arg2;
        _arg2_0000FC07 = arg3;
        _arg3_0000FC0B = arg4;
        _arg4_0000FC0F = arg5;
        _arg5_0000FC13 = arg6;
        _arg6_0000FC17 = arg7;
        D_800FE408 = 0;
        D_80119A70 = pfsCmd;
        D_800FA2FC_0000FBFB = pfsCmd;
        return 1;
    }
    return 0;
}
#endif
// yield_self_1ms();
#if 0
RECOMP_PATCH int MusHandleAsk(musHandle handle) {
    channel_t* cp;
    int i, count;
    recomp_printf(" max_channels_0000FCC3 %d\n",max_channels_0000FCC3);
    if (!handle)
        return (0);

    for (i = 0, cp = mus_channels_0000FCCB, count = 0; i < max_channels_0000FCC3; i++, cp++) {
        if (cp->handle == handle) {
            count++;
        }
    }
    return (count);
}
#endif