#include "GPIO/GPIOlib.h"

using namespace GPIO;

const double kp = 0.35;
const double ki = 0.65;
const double kd = 0.005;
const double A = kp + ki + kd;
const double B = -2 * kd - kp;
const double C = kd;
const int DEGREE = 30;

double firPreErr = 0;
double secPreErr = 0;
double preResult = 0;

void control(double left, double right){
    double err = left - right;
    double increment = A * err + B * firPreErr + C * secPreErr;
    preResult += increment;

    secPreErr = firPreErr;
    firPreErr = err;

    int direction =  DEGREE * (preResult / 10.0);
    direction = direction > DEGREE? DEGREE: direction;

    turnTo(direction);
    delay(50);
}

