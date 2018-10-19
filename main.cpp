//
// Created by leich on 2018/10/19.
//
//
// Created by leich on 2018/10/19.
//
#include "carControl/CarControl.h"
#include <iostream>

int main() {
    /*
     * 初始化
     */
    //控制部分初始化
    ControlConfigs controlConfigs;
    getControlConfig(controlConfigs);

    std::cout << controlConfigs.controlMethod << std::endl;
    std::cout << controlConfigs.kp << std::endl;
    std::cout << controlConfigs.ki << std::endl;
    std::cout << controlConfigs.kd << std::endl;
    std::cout << controlConfigs.leftStdSpeed << std::endl;
    std::cout << controlConfigs.rightStdSpeed << std::endl;

    const int CONTROL_PARAMETER_NUMBER = 3;
    const double PI = 3.14;
    //传给小车控制的参数
    //0：左边线距离
    //1：右边线距离
    //2：角度（从右往左）
    double controlParameters[CONTROL_PARAMETER_NUMBER] = {0, 0, PI / 2.0};

    while(true) {
        /*
         * 图片处理
         */

        /*
         * 小车控制
         */
    }

}
