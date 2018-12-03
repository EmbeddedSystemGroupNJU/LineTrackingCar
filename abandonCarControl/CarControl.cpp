//
// Created by leich on 2018/10/19.
//
#include "CarControl.h"
#include "CarControlMethod.h"
#include "GPIO/GPIOlib.h"
#include <iostream>

using namespace GPIO;

const int MAX_SPEED = 10;
const int TURN_ANGLE = 10;
const double THRESHOLD = 0.7;

void controlCar(
        Distances &preDists,
        Speeds &preSpeeds,
        Distances &currDists,
        Speeds &currSpeeds,
        Speeds &stdSpeeds,
        PID &leftPid,
        PID &rightPid)
{

    Speeds processSpeeds = Speeds(0, 0);
    processSpeeds = rightDistancePidControl(preDists, stdSpeeds, rightPid);


    if (processSpeeds.left > MAX_SPEED){
        processSpeeds.left = MAX_SPEED;
    } else if (processSpeeds.left < -MAX_SPEED){
        processSpeeds.left = -MAX_SPEED;
    }

    if (processSpeeds.right > MAX_SPEED) {
        processSpeeds.right = MAX_SPEED;
    } else if (processSpeeds.right < -MAX_SPEED) {
        processSpeeds.right = -MAX_SPEED;
    }
    currSpeeds.left = processSpeeds.left;
    currSpeeds.right = processSpeeds.right;

    double leftRate = preDists.left / (preDists.left + preDists.right);
    double rightRate = preDists.right / (preDists.left + preDists.right);

    init();

    if (leftRate > THRESHOLD) {
        turnTo(TURN_ANGLE);
    } else if (rightRate > THRESHOLD) {
        turnTo(-TURN_ANGLE);
    } else{
        turnTo(0);
    }

    if (processSpeeds.left < 0){
        controlLeft(BACKWARD, (int)processSpeeds.left);
    } else{
        controlLeft(FORWARD, (int)processSpeeds.left);
    }
    if (processSpeeds.right < 0) {
        controlRight(BACKWARD, (int)processSpeeds.right);
    }else {
        controlRight(FORWARD, (int)processSpeeds.right);
    }
    std::cout << currSpeeds << std::endl;
}