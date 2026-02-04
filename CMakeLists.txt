cmake_minimum_required(VERSION 4.1)
project(referee_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(referee_system main.cpp
        baserobot.h
        infantryrobot.cpp
        infantryrobot.h
        engineerrobot.h
        robotmanager.cpp
        robotmanager.h)
