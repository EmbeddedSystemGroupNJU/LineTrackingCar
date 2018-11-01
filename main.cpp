//
// Created by leich on 2018/10/19.
//

#include "carControl/class/ControlConfigs.h"
#include "carControl/GetControlConfig.h"
#include "carControl/CarControl.h"
#include <iostream>
#include <cmath>
#include "imageProcess/process.cpp"

int main() {
    /*
     * 初始化
     */
    //控制部分初始化
    ControlConfigs controlConfigs;
    getControlConfig(controlConfigs);

    PID *leftPid = new PID(controlConfigs.kp, controlConfigs.ki, controlConfigs.kd);
    PID *rightPid = new PID(controlConfigs.kp, controlConfigs.ki, controlConfigs.kd);
    //std::cout << *rightPid << std::endl;

    const int CONTROL_PARAMETER_NUMBER = 3;
    const double PI = 3.14;
    //传给小车控制的参数
    //0：左边线距离
    //1：右边线距离
    //2：角度（从右往左）
    double controlParams[CONTROL_PARAMETER_NUMBER] = {0, 0, PI / 2.0};
    Speeds stdSpeeds = Speeds(controlConfigs.leftStdSpeed, controlConfigs.rightStdSpeed);

    Distances preDists = Distances(300, 700);
    Speeds preSpeeds = stdSpeeds;
    double preDir = PI / 2;

    Distances currDists = preDists;
    Speeds currSpeeds = preSpeeds;
    double currDir = preDir;
	

    /**
     * 相机初始化
     * */
    VideoCapture capture(CAM_PATH);
    //If this fails, try to open as a video camera, through the use of an integer param
    if (!capture.isOpened())
    {
        capture.open(atoi(CAM_PATH.c_str()));
    }

    double dWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH);			//the width of frames of the video
    double dHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT);		//the height of frames of the video
    clog<<"Frame Size: "<<dWidth<<"x"<<dHeight<<endl;
    //init()
    Mat image;


	
    while(true) {
        /*
         * 图片处理
         */
        capture>>image;
        if(image.empty())
            break;
        double ret;
        process_img(image,controlParams);

	
        /*
         * 小车控制
         */
        currDists.left = controlParams[0];
        currDists.right = controlParams[1];
        currDir = controlParams[2];

        controlCar(preDists, preSpeeds,
                   currDists, currSpeeds,
                   stdSpeeds,
                   *leftPid, *rightPid);
        
        preDists = currDists;
        preSpeeds = currSpeeds;
        preDir = currDir;

        /*
         * 测试
         */
        //只控制右边线
//        double deltaDis = (currSpeeds.right - currSpeeds.left) * 1.0;
//        currDists = Distances(
//			preDists.left - deltaDis,
//			preDists.right + deltaDis
//		);
//        //控制两边线
//        double deltaDis = (currSpeeds.right - currSpeeds.left) * 1.0;
//        currDists = Distances(
//                preDists.left - deltaDis,
//                preDists.right + deltaDis
//        );
//        currDir = rand() / double(RAND_MAX) * (3.14);
//
//        std::cout << currDists << std::endl;
//        if(std::abs(currSpeeds.left - currSpeeds.right) < 0.001) break;
    }

}
