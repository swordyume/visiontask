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
        return robot -> get_team() == team && robot -> get_id() == id;
    });
}

void RobotManager::destory(RobotVec::iterator it) {
    const auto &robot = * it;

    output_ . push_back("D " + to_string(robot -> get_team()) + " " + to_string(robot -> get_id()));

    bad_robots_ . push_back(robot);
    good_robots_ . erase(it);
}

void RobotManager::ProcessHeat(uint16_t current_time) {
    if (current_time <= last_time_) {
        return;
    }

    uint16_t delta_time = current_time - last_time_;

    for (size_t i = 0; i < good_robots_ . size();) {
        auto robot = good_robots_[i];

        if (! robot) {
            good_robots_ . erase(good_robots_ . begin() + i);
            continue;
        }

        uint16_t new_heat = robot -> get_heat() > delta_time ? robot -> get_heat() - delta_time : 0;
        uint16_t max_damage = robot -> get_heat() > robot -> get_max_heat()? robot -> get_heat() - robot -> get_max_heat(): 0;
        uint16_t real_damage = max_damage > delta_time ? delta_time : max_damage;
        uint16_t new_blood = robot -> get_blood() > real_damage ? robot -> get_blood() - real_damage : 0;
        robot -> set_heat(new_heat);
        robot -> set_blood(new_blood);

        if (robot -> get_blood() <= 0) {
            auto it = FindRobot(good_robots_, robot -> get_team(), robot -> get_id());
            destory(it);
            continue;
        }
        i++;
    }
    last_time_ = current_time;
}

void RobotManager::CmdA(uint16_t team, uint16_t id, uint8_t type) {
    auto destoryed_it = FindRobot(bad_robots_, team, id);
    const auto &destoryed_robot = * destoryed_it;

    if (destoryed_it != bad_robots_ . end() && destoryed_robot -> get_type() == type) {
        good_robots_ . push_back(destoryed_robot);
        bad_robots_ . erase(destoryed_it);
        destoryed_robot -> reset_blood();
        destoryed_robot -> reset_heat();
        return;
    } else {
        auto it = FindRobot(good_robots_, team, id);

        if (it != good_robots_ . end()) {
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
            good_robots_ . push_back(new_robot);
        }
    }
}

void RobotManager::CmdF(uint16_t team, uint16_t id, uint16_t damage) {
    auto it = FindRobot(good_robots_, team, id);

    if (it == good_robots_ . end()) {
        return;
    } else {
        const auto &robot = * it;
        uint16_t new_blood = robot -> get_blood() > damage ? robot -> get_blood() - damage : 0;
        if (new_blood > 0) {
            robot -> set_blood(new_blood);
        } else {
            destory(it);
        }
    }
}

void RobotManager::CmdH(uint16_t team, uint16_t id, uint16_t add_heat) {
    auto it = FindRobot(good_robots_, team, id);

    if (it == good_robots_ . end()) {
        return;
    } else {
        const auto &robot = * it;
        if (robot -> get_type() != 0) {
            return;
        } else if (robot -> get_type() == 0) {
            uint16_t new_heat = robot -> get_heat() + add_heat;
            robot -> set_heat(new_heat);
        }
    }
}

void RobotManager::CmdU(uint16_t team, uint16_t id, uint8_t level) {
    auto it = FindRobot(good_robots_, team, id);

    if (it == good_robots_ . end()) {
        return;
    } else {
        const auto &robot = * it;
        if (robot -> get_type() != 0) {
            return;
        } else if (robot -> get_type() == 0) {
            auto infantry = dynamic_cast<InfantryRobot *>(robot . get());
            if (infantry) {
                infantry -> set_level(level);
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
