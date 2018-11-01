//
// Created by leich on 2018/10/19.
//

#ifndef LINETRACKINGCAR_CONTROLCONFIGS_H
#define LINETRACKINGCAR_CONTROLCONFIGS_H

#include <string>

class ControlConfigs {
public:
    std::string controlMethod;
    double kp;
    double ki;
    double kd;
    double leftStdSpeed;
    double rightStdSpeed;
    int maxSpeed;
};

#endif //LINETRACKINGCAR_CONTROLCONFIGS_H
