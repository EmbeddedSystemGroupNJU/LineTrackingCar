//
// Created by leich on 2018/10/19.
//

#include "CarControlMethod.h"
#include <cmath>

double getDeltaSpeed(double newDis, double mid, double oldSpeed)
{
    return (newDis - mid) * oldSpeed / mid;
}

Speeds rightDistancePidControl(
        const Distances& preDistances,
        const Speeds &stdSpeeds,
        PID &pid)
{
    double mid = (preDistances.left + preDistances.right) / (double)2.0;

    //获得由PID控制的右边线距离
    double processRightDis = pid.getProcessValue(mid, preDistances.right);

    //获得新的速度
    double newLeftSpeed =
            stdSpeeds.left + getDeltaSpeed(processRightDis, mid, stdSpeeds.left);
    double newRightSpeed =
            stdSpeeds.right - getDeltaSpeed(processRightDis, mid, stdSpeeds.right);

    Speeds newSpeeds = Speeds(newLeftSpeed, newRightSpeed);
    return newSpeeds;
}

Speeds bothDistancePidControl(
        Distances &preDistances,
        Speeds &preSpeeds,
        double preDirection,
        Distances &currDistances,
        Speeds &stdSpeeds,
        PID &leftPid,
        PID &rightPid)
{

    double avgSpeed = (preSpeeds.left + preSpeeds.right) / 2.0;

    //根据"目标左边线距离"和"实际左边线距离"计算控制后的左边线距离
    double estimateLeftDistance = preDistances.left + avgSpeed * cos(preDirection);
    double acutalLeftDistance = currDistances.left;
    double processLeftDistance = leftPid.getProcessValue(estimateLeftDistance, acutalLeftDistance);

    //根据"目标右边线距离"和"实际右边线距离"计算控制后的右边线距离
    double estimateRightDistance = preDistances.right - avgSpeed * cos(preDirection);
    double actualRightDistance = currDistances.right;
    double processRightDistance = rightPid.getProcessValue(estimateRightDistance, actualRightDistance);

    //根据所获得的控制后距离获得新速度
    double processMid = (processLeftDistance + processRightDistance) / 2.0;
    double newLeftSpeed = processMid * stdSpeeds.left / processLeftDistance;
    double newRightSpeed = processMid * stdSpeeds.right / processRightDistance;

    Speeds newSpeeds = Speeds(newLeftSpeed, newRightSpeed);
    return newSpeeds;
}