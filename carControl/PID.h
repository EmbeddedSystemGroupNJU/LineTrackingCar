//
// Created by leich on 2018/10/19.
//

#ifndef LINETRACKINGCAR_PID_H
#define LINETRACKINGCAR_PID_H

#include <iostream>

/*
 * 增量式PID控制器
 */
class PID {
private:
    //PID系数，Kp，Ki，Kd
    double kp;
    double ki;
    double kd;

    //目标值
    double targetValue;
    //实际值
    double actualValue;

    //当前误差值e(k)
    double error;
    //前一次的误差值e(k-1)
    double firstPreviousError;
    //更前一次的误差值e(k-2)
    double secondPreviousError;

    //求增量值时，公式的系数 Δyn = A * e(n) + B * e(n-1) + C * e(n-2)
    double A_Coefficient;
    double B_Coefficient;
    double C_Coefficient;

public:
    PID(double kp, double ki, double kd);
    ~PID();

    /*
     * 获得PID输出值
     * @param target 目标值
     * @param actual 实际值
     * @return PID输出值
     */
    double getProcessValue(double target, double actual);

    friend std::ostream & operator<<(std::ostream &os, const PID &pid);
};

#endif //LINETRACKINGCAR_PID_H
