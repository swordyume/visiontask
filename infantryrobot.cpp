//
// Created by lhb on 2026/2/2.
//

#include "infantryrobot.h"

bool InfantryRobot::SetLevel(uint8_t level) {
    if (level < 1 || level > 3 || level <= level_) {
        return false;
    }

    switch (level) {
        case 1:
            max_blood_ = 100;
            max_heat_ = 100;
            break;
        case 2:
            max_blood_ = 150;
            max_heat_ = 200;
            break;
        case 3:
            max_blood_ = 250;
            max_heat_ = 300;
            break;
    }

    level_ = level;

    ResetBlood();
    ResetHeat();

    return true;
}
