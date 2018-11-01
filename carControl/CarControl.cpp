//
// Created by leich on 2018/10/19.
//
#include "CarControl.h"
#include "CarControlMethod.h"
#include "../GPIOlib.h"
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
        PID &rightPid,
        int maxSpeed)
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
    if(processSpeeds.left < 0) {
        if(processSpeeds.left < -maxSpeed){
		controlLeft(BACKWARD, maxSpeed);
        }else {
		controlLeft(BACKWARD, -(int)processSpeeds.left);
	}
    } else{
	if(processSpeeds.left > maxSpeed){
		controlLeft(FORWARD, maxSpeed);
        }else {
		controlLeft(FORWARD, (int)processSpeeds.left);
	}
    }
    if(processSpeeds.right < 0) {
        if(processSpeeds.right < -maxSpeed){
		controlRight(BACKWARD, maxSpeed);
        }else {
		controlRight(BACKWARD, -(int)processSpeeds.right);
	}
    } else{
        if(processSpeeds.right > maxSpeed){
		controlRight(FORWARD, maxSpeed);
        }else {
		controlRight(FORWARD, (int)processSpeeds.right);
	}
    }
    std::cout << currSpeeds << std::endl;
}
