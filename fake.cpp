#include <iostream>
#include <cmath>
#include "imageProcess/process.cpp"
#include "GPIOlib.h"
using namespace GPIO;

int left = 10;
int right = 10;

void turn_left(){
	left = 5;
	right = 15;
}

void turn_right(){
	right = 5;
	left = 15;
}


void adj_v(int ldis, int ridis){
	if(ldis-rdis>50){
		turn_left();
		
	}
	if(rdis-ldis>50){
		turn_right();	
	}
	controlLeft(FORWARD, left);
	controlRight(FORWARD, right);
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

	while(true) {
		/*
         * 图片处理
         */
		double ret[2];
		ret[0] = 0;
		ret[1] = 0;
		capture>>image;
		if(image.empty())
			break;
		double ret;
		process_img(image,ret);

		/*
         * 小车控制
         */
		adj_v(ret[0], ret[1]);
	}
}