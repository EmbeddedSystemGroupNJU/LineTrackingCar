//
// Created by leich on 2018/10/19.
//

#include "PID.h"

PID::PID(double p, double i, double d)
{
    this->kp = p;
    this->ki = i;
    this->kd = d;

    this->targetValue = 0;
    this->actualValue = 0;

    this->error = 0;
    this->firstPreviousError = 0;
    this->secondPreviousError = 0;

    //A = Kp * (1 + T/Ti + Td/T)
    this->A_Coefficient = p + i + d;
    //B = -Kp * [1 + (2 * Td) /T]
    this->B_Coefficient = -2 * d - p;
    //C = Kp * (Td /T)
    this->C_Coefficient = d;
}

PID::~PID(){}

double PID::getProcessValue(double target, double actual)
{
    this->targetValue = target;
    this->actualValue = actual;

    this->error = this->targetValue - this->actualValue;

    //Δyn = A * e(n) + B * e(n-1) + C * e(n-2)
    double incrementalResult =
            this->A_Coefficient * this->error +
            this->B_Coefficient * this->firstPreviousError +
            this->C_Coefficient * this->secondPreviousError;
    double processValue = this->actualValue + incrementalResult;

    //更新误差值
    this->secondPreviousError = this->firstPreviousError;
    this->firstPreviousError = this->error;

    return processValue;
}

std::ostream & operator<<(std::ostream & os, const PID & pid)
{
    os << "***************PID controller Info****************" << std::endl;
    os << "    Kp = " << pid.kp << std::endl;
    os << "    Ki = " << pid.ki << std::endl;
    os << "    Kd = " << pid.kd << std::endl;
    os << "target = " << pid.targetValue << std::endl;
    os << "actual = " << pid.actualValue << std::endl;
    os << "  e(k) = " << pid.error << std::endl;
    os << "e(k-1) = " << pid.firstPreviousError << std::endl;
    os << "e(k-2) = " << pid.secondPreviousError << std::endl;
    os << "*************************************************" << std::endl;

    return os;
}