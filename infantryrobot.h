//
// Created by lhb on 2026/2/2.
//

#ifndef REFEREE_SYSTEM_INFANTRYROBOT_H
#define REFEREE_SYSTEM_INFANTRYROBOT_H

#include "baserobot.h"

class InfantryRobot :public BaseRobot{
public:
    InfantryRobot(uint16_t team_,uint16_t id_): BaseRobot(team_,id_,0){
        max_blood_ = 100;
        max_heat_ = 100;
        level_ = 1;

        reset_blood();
        reset_heat();
    }

    bool set_level(uint8_t level) override;
    [[nodiscard]]uint8_t get_level() const {return level_;}

private:
    uint8_t level_;
};


#endif //REFEREE_SYSTEM_INFANTRYROBOT_H