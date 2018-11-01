//
// Created by leich on 2018/10/19.
//

#ifndef LINETRACKINGCAR_CARCONTROL_H
#define LINETRACKINGCAR_CARCONTROL_H

#include "class/PID.h"
#include "class/Distances.h"
#include "class/Speeds.h"
#include <string>

void controlCar(
        Distances &preDists,
        Speeds &preSpeeds,
        Distances &currDists,
        Speeds &currSpeeds,
        Speeds &stdSpeeds,
        PID &leftPid,
        PID &rightPid);

#endif //LINETRACKINGCAR_CARCONTROL_H
