#include "GPIO/GPIOlib.h"
#include <iostream>

using namespace GPIO;
using namespace std;

const double kp = 0.35;
const double ki = 0.65;
const double kd = 0.005;
const int STD_DEGREE = 20;
const int MAX_DEGREE = 30;
const double NORM = 10.0;
const int DELAY = 50;

double sumErr = 0;
double preErr = 0;

void control(double left, double right){
    double mid = (left + right) / (double)2.0;

    double err = right - mid;
    sumErr += err;
    double diff = err - preErr;

    preErr = err;

    double result = kp * err + ki * sumErr + kd * diff;

    int direction =  STD_DEGREE * (result / right);
    direction = direction > MAX_DEGREE? MAX_DEGREE: direction;

    cout << "pid result:" << result << endl;
    cout << "direction: " << direction << endl;
    turnTo(direction);
    delay(DELAY);
}
