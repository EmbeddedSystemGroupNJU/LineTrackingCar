#include "GPIO/GPIOlib.h"
#include <iostream>

using namespace GPIO;
using namespace std;

const int FIRST_THRESHOLD = 50;
const int FIRST_DEGREE = 15;
const int FIRST_DELAY = 30;

const int SECOND_THRESHOLD = 100;
const int SECOND_DEGREE = 25;
const int SECOND_DELAY = 20;


const int STRAIGHT_DELAY = 30;

void control(double left, double right){
    if (left - right < FIRST_THRESHOLD && right - left < FIRST_THRESHOLD){
        turnTo(0);
        delay(STRAIGHT_DELAY);
    }else if(left - right > FIRST_THRESHOLD){
        turnTo(-FIRST_DEGREE);
        delay(FIRST_DELAY);
        cout << "turn left: " << FIRST_DEGREE << endl;
    }else if(right - left > FIRST_THRESHOLD){
        turnTo(FIRST_DEGREE);
        delay(FIRST_DELAY);
        cout << "turn right: " << FIRST_DEGREE << endl;
    }else if(left - right > SECOND_THRESHOLD){
        turnTo(-SECOND_DEGREE);
        delay(SECOND_DELAY);
        cout << "turn left: " << SECOND_DEGREE << endl;
    }else if(right - left > SECOND_THRESHOLD){
        turnTo(SECOND_DEGREE);
        delay(SECOND_DELAY);
        cout << "turn right: " << SECOND_DEGREE << endl;
    }
}

