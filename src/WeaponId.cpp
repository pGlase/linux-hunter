#include "WeaponId.hpp"

std::string GetShortname(WeaponId id)
{
    switch(id){
        case WeaponId::GREATSWORD:
            return "GS";
        case WeaponId::SWORD_AND_SHIELD:
            return "SNS";
        case WeaponId::DUAL_BLADES:
            return "DB";
        case WeaponId::LONGSWORD:
            return "LS";
        case WeaponId::HAMMER:
            return "BONK";
        case WeaponId::HUNTING_HORN:
            return "HH";
        case WeaponId::LANCE:
            return "LA";
        case WeaponId::GUN_LANCE:
            return "GL";
        case WeaponId::SWITCH_AXE:
            return "SA";
        case WeaponId::CHARGE_BLADE:
            return "CB";
        case WeaponId::INSECT_GLAIVE:
            return "IG";
        case WeaponId::BOW:
            return "BO";
        case WeaponId::HEAVY_BOWGUN:
            return "HBG";
        case WeaponId::LIGHT_BOWGUN:
            return "LBG";
        default:
            throw "ERROR";
    };
}

