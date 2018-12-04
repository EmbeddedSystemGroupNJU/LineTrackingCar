#include <iostream>
#include <cmath>
#include "imageProcess/process.cpp"
#include "GPIOlib.h"
using namespace GPIO;


void adj_v(double ldis, double rdis){
    if (ldis-rdis<50 && ldis-rdis>-50){
        turnTo(0);
        delay(30);
    }
    else if(ldis-rdis>50){
        turnTo(-15);
        delay(20);
        cout<<"turn left"<<endl;
        
    }
    else if(rdis-ldis>50){
        turnTo(15);
        delay(20);
        cout<<"turn right"<<endl;
        
    }
    else if(ldis-rdis>100){
		turnTo(-25);  
		delay(15);
		cout<<"turn left"<<endl;
		//turnTo(0);
		//ssdelay(30);
	}
	else if(rdis-ldis>100){
		turnTo(25);
		delay(15);
		cout<<"turn right"<<endl;
		//turnTo(0);
		//delay(15);
	}

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
	controlLeft(FORWARD, 10);
	controlRight(FORWARD, 10);

    double ret[2];
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

		/*
         * 小车控制
         */
		adj_v(ret[0], ret[1]);
		if(waitKey(1)=='q'){break;}
	}
	stopLeft();
	stopRight();
}
