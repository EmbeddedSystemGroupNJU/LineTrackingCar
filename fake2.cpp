#include <iostream>
#include <cmath>
#include "imageProcess/process.cpp"
#include "GPIOlib.h"
using namespace GPIO;

int adj = 0;
int last_adj = 0;
int error = 0;
double part = 0.6;
double diff = 0.5;
double actual = 0.02;

void adj_v(int ldis, int rdis){
    error = adj- last_adj;
    last_adj = adj;
    adj = (int)((double)(part*adj)+(double)((rdis-ldis)*actual) + (double)(error*diff));
    turnTo(adj);
    delay(30);
}

int main(){
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

    init();
    controlLeft(FORWARD, 5);
    controlRight(FORWARD, 5);

    int ret[2];
    while(true) {
        /*
         * 图片处理
         */
        ret[0] = 0;
        ret[1] = 0;
        capture>>image;
        if(image.empty())
            break;

        process_img(image,ret);
        process_img(image, ret);
        /*
         * 小车控制
         */
        adj_v(ret[0], ret[1]);
        if(waitKey(1)=='q'){break;}
    }
    stopLeft();
    stopRight();
}
