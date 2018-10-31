//
// Created by leich on 2018/10/19.
//
#include "CarControl.h"
#include "CarControlMethod.h"
#include "GPIO/GPIOlib.h"
#include <iostream>

using namespace GPIO;

void controlCar(
        Distances &preDists,
        Speeds &preSpeeds,
        double preDir,
        Distances &currDists,
        Speeds &currSpeeds,
        Speeds &stdSpeeds,
        std::string &controlMethod,
        PID &leftPid,
        PID &rightPid)
{

    Speeds processSpeeds = Speeds(0, 0);
    if (controlMethod == "RIGHT_DISTANCE_CONTROL") {
        processSpeeds = rightDistancePidControl(preDists, stdSpeeds, rightPid);
    }else if (controlMethod == "BOTH_DISTANCE_CONTROL") {
        processSpeeds = bothDistancePidControl(preDists, preSpeeds, preDir, currDists, stdSpeeds, leftPid, rightPid);
    }
    currSpeeds.left = processSpeeds.left;
    currSpeeds.right = processSpeeds.right;
    init();
    turnTo(0);
	controlLeft(FORWARD, (int)processSpeeds.left);
	controlRight(FORWARD, (int)processSpeeds.right);
    std::cout << currSpeeds << std::endl;
}