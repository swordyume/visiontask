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

    virtual bool set_level(uint8_t level)=0;

    [[nodiscard]] uint16_t get_team() const { return team_; }
    [[nodiscard]] uint16_t get_id() const { return id_; }
    [[nodiscard]] uint8_t get_type() const { return type_; }
    [[nodiscard]] uint16_t get_blood() const { return blood_; }
    [[nodiscard]] uint16_t get_heat() const { return heat_; }
    [[nodiscard]] uint16_t get_max_blood() const { return max_blood_; }
    [[nodiscard]] uint16_t get_max_heat() const { return max_heat_; }

    void set_blood(uint16_t blood) { blood_ = blood; }
    void set_heat(uint16_t heat) { heat_ = heat; }
    void reset_blood() { blood_ = max_blood_ ; }
    void reset_heat() { heat_ = 0 ; }


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