//
// Created by lhb on 2026/2/2.
//


#ifndef REFEREE_SYSTEM_BASEROBOT_H
#define REFEREE_SYSTEM_BASEROBOT_H

#include <iostream>
using namespace std;

class BaseRobot {
public:
    BaseRobot(uint16_t team, uint16_t id, uint8_t type) : team_(team), id_(id), type_(type), blood_(0),
                                                         heat_(0), max_blood_(0), max_heat_(0) {}

    virtual ~BaseRobot() =default;

    virtual bool SetLevel(uint8_t level)=0;

    [[nodiscard]] uint16_t GetTeam() const { return team_; }
    [[nodiscard]] uint16_t GetId() const { return id_; }
    [[nodiscard]] uint8_t GetType() const { return type_; }
    [[nodiscard]] uint16_t GetBlood() const { return blood_; }
    [[nodiscard]] uint16_t GetHeat() const { return heat_; }
    [[nodiscard]] uint16_t GetMaxBlood() const { return max_blood_; }
    [[nodiscard]] uint16_t GetMaxHeat() const { return max_heat_; }

    void SetBlood(uint16_t blood) { blood_ = blood; }
    void SetHeat(uint16_t heat) { heat_ = heat; }
    void ResetBlood() { blood_ = max_blood_ ; }
    void ResetHeat() { heat_ = 0 ; }


protected:
    uint16_t team_;
    uint16_t id_;
    uint8_t type_;
    uint16_t blood_;
    uint16_t heat_;
    uint16_t max_blood_;
    uint16_t max_heat_;
};


#endif //REFEREE_SYSTEM_BASEROBOT_H