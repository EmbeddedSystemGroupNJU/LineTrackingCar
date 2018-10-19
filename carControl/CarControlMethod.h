//
// Created by leich on 2018/10/19.
//

#ifndef LINETRACKINGCAR_CARCONTROLMETHOD_H
#define LINETRACKINGCAR_CARCONTROLMETHOD_H

#include "class/PID.h"
#include "class/Distances.h"
#include "class/Speeds.h"

Speeds rightDistancePidControl(
        Distances &oldDis,
        Speeds &stdSpeeds,
        PID &pid
        );

Speeds bothDistancePidControl(
        Distances &preDistances,
        Speeds &preSpeeds,
        double preDirection,
        Distances &currDistances,
        Speeds &standardSpeeds,
        PID &leftPid,
        PID &rightPid
        );


#endif //LINETRACKINGCAR_CARCONTROLMETHOD_H
