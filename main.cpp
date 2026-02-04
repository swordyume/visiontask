#include "robotmanager.h"

#include <iostream>

using namespace std;

int main() {
    RobotManager manager;

    uint32_t N;
    cin >> N;

    uint16_t current_time;
    char cmd;
    uint16_t p1;
    uint16_t p2;
    uint16_t p3;

    for (int i = 0; i < N; i++) {
        cin >> current_time >> cmd >> p1 >> p2 >> p3;
        manager.ProcessCommand(current_time, cmd, p1, p2, p3);
    }

    manager.StandPrint();

    return 0;
}
