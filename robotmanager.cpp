//
// Created by lhb on 2026/2/2.
//

#include "robotmanager.h"

#include "infantryrobot.h"
#include "engineerrobot.h"

#include <algorithm>

using namespace std;

RobotManager::RobotVec::iterator RobotManager::FindRobot(RobotVec &robots, uint16_t team, uint16_t id) {
    return ranges::find_if(robots, [&](const shared_ptr<BaseRobot> &robot) -> bool {
        return robot -> GetTeam() == team && robot -> GetId() == id;
    });
}

void RobotManager::destory(RobotVec::iterator it) {
    const auto &robot = * it;

    output_ . push_back("D " + to_string(robot -> GetTeam()) + " " + to_string(robot -> GetId()));

    bad_robots . push_back(robot);
    good_robots . erase(it);
}

void RobotManager::ProcessHeat(uint16_t current_time) {
    if (current_time <= last_time_) {
        return;
    }

    uint16_t delta_time = current_time - last_time_;

    for (size_t i = 0; i < good_robots . size();) {
        auto robot = good_robots[i];

        if (! robot) {
            good_robots . erase(good_robots . begin() + i);
            continue;
        }

        uint16_t new_heat = robot -> GetHeat() > delta_time ? robot -> GetHeat() - delta_time : 0;
        uint16_t max_damage = robot -> GetHeat() > robot -> GetMaxHeat()? robot -> GetHeat() - robot -> GetMaxHeat(): 0;
        uint16_t real_damage = max_damage > delta_time ? delta_time : max_damage;
        uint16_t new_blood = robot -> GetBlood() > real_damage ? robot -> GetBlood() - real_damage : 0;
        robot -> SetHeat(new_heat);
        robot -> SetBlood(new_blood);

        if (robot -> GetBlood() <= 0) {
            auto it = FindRobot(good_robots, robot -> GetTeam(), robot -> GetId());
            destory(it);
            continue;
        }
        i++;
    }
    last_time_ = current_time;
}

void RobotManager::CmdA(uint16_t team, uint16_t id, uint8_t type) {
    auto destoryed_it = FindRobot(bad_robots, team, id);
    const auto &destoryed_robot = * destoryed_it;

    if (destoryed_it != bad_robots . end() && destoryed_robot -> GetType() == type) {
        good_robots . push_back(destoryed_robot);
        bad_robots . erase(destoryed_it);
        destoryed_robot -> ResetBlood();
        destoryed_robot -> ResetHeat();
        return;
    } else {
        auto it = FindRobot(good_robots, team, id);

        if (it != good_robots . end()) {
            return;
        } else {
            shared_ptr<BaseRobot> new_robot;
            if (type == 0) {
                new_robot = make_shared<InfantryRobot>(team, id);
            } else if (type == 1) {
                new_robot = make_shared<EngineerRobot>(team, id);
            } else {
                return;
            }
            good_robots . push_back(new_robot);
        }
    }
}

void RobotManager::CmdF(uint16_t team, uint16_t id, uint16_t damage) {
    auto it = FindRobot(good_robots, team, id);

    if (it == good_robots . end()) {
        return;
    } else {
        const auto &robot = * it;
        uint16_t new_blood = robot -> GetBlood() > damage ? robot -> GetBlood() - damage : 0;
        if (new_blood > 0) {
            robot -> SetBlood(new_blood);
        } else {
            destory(it);
        }
    }
}

void RobotManager::CmdH(uint16_t team, uint16_t id, uint16_t add_heat) {
    auto it = FindRobot(good_robots, team, id);

    if (it == good_robots . end()) {
        return;
    } else {
        const auto &robot = * it;
        if (robot -> GetType() != 0) {
            return;
        } else if (robot -> GetType() == 0) {
            uint16_t new_heat = robot -> GetHeat() + add_heat;
            robot -> SetHeat(new_heat);
        }
    }
}

void RobotManager::CmdU(uint16_t team, uint16_t id, uint8_t level) {
    auto it = FindRobot(good_robots, team, id);

    if (it == good_robots . end()) {
        return;
    } else {
        const auto &robot = * it;
        if (robot -> GetType() != 0) {
            return;
        } else if (robot -> GetType() == 0) {
            auto infantry = dynamic_cast<InfantryRobot *>(robot . get());
            if (infantry) {
                infantry -> SetLevel(level);
            }
        }
    }
}

void RobotManager::ProcessCommand(uint16_t current_time, char cmd, uint16_t p1, uint16_t p2, uint16_t p3) {
    ProcessHeat(current_time);
    switch (cmd) {
        case 'A':
            CmdA(p1, p2, static_cast<uint8_t>(p3));
            break;
        case 'F':
            CmdF(p1, p2, p3);
            break;
        case 'H':
            CmdH(p1, p2, p3);
            break;
        case 'U':
            CmdU(p1, p2, static_cast<uint8_t>(p3));
            break;
        default:
            break;
    }
}

void RobotManager::StandPrint() const {
    for (const auto &str: output_) {
        cout << str << endl;
    }
};
