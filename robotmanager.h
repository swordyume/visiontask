//
// Created by lhb on 2026/2/2.
//

#ifndef REFEREE_SYSTEM_ROBOTMANAGER_H
#define REFEREE_SYSTEM_ROBOTMANAGER_H
#include "baserobot.h"

#include <vector>
#include <memory>
#include <string>

class RobotManager {
public:
    RobotManager() : last_time_(0) {}

    void ProcessCommand(uint16_t current_time, char cmd, uint16_t p1, uint16_t p2, uint16_t p3);
    void StandPrint() const;

    [[nodiscard]] uint16_t GetLastTime() const { return last_time_; }

private:
    std::vector<std::shared_ptr<BaseRobot> > good_robots;
    std::vector<std::shared_ptr<BaseRobot> > bad_robots;
    std::vector<std::string> output_;

    uint16_t last_time_;

    using RobotVec = std::vector<std::shared_ptr<BaseRobot> >;

    static RobotVec::iterator FindRobot(RobotVec &robots, uint16_t team, uint16_t id);

    void destory(RobotVec::iterator it);
    void CmdA(uint16_t team, uint16_t id, uint8_t type);
    void CmdF(uint16_t team, uint16_t id, uint16_t damage);
    void CmdH(uint16_t team, uint16_t id, uint16_t add_heat);
    void CmdU(uint16_t team, uint16_t id, uint8_t level);
    void ProcessHeat(uint16_t current_time);
};


#endif //REFEREE_SYSTEM_ROBOTMANAGER_H
