#pragma once
#include <string>

enum class WeaponId : int {
    GREATSWORD,
    SWORD_AND_SHIELD,
    DUAL_BLADES,
    LONGSWORD,
    HAMMER,
    HUNTING_HORN,
    LANCE,
    GUN_LANCE,
    SWITCH_AXE,
    CHARGE_BLADE,
    INSECT_GLAIVE,
    BOW,
    HEAVY_BOWGUN,
    LIGHT_BOWGUN,
    NONE = 255
};

std::string GetShortname(WeaponId id);
