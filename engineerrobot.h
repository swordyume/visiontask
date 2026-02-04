//
// Created by lhb on 2026/2/2.
//

#ifndef REFEREE_SYSTEM_ENGINEERROBOT_H
#define REFEREE_SYSTEM_ENGINEERROBOT_H
#include "baserobot.h"

#include <cstdint>

class EngineerRobot : public BaseRobot {
public:
    EngineerRobot(uint16_t team, uint16_t id) : BaseRobot(team, id, 1) {
        max_blood_ = 300;
        max_heat_ = 0;
        ResetBlood();
        ResetHeat();
    };

    bool SetLevel(uint8_t level) override { return false; };
};


#endif //REFEREE_SYSTEM_ENGINEERROBOT_H
