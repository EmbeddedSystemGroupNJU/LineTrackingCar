#include <iostream>
#include "imageProcess/process.cpp"
#include "carControl/initControl.cpp"
#include "carControl/control_1.cpp"

using namespace std;

int main(){
    VideoCapture capture(CAM_PATH);
    if (!capture.isOpened()) {
        capture.open(atoi(CAM_PATH.c_str()));
    }

    double dWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH);			//the width of frames of the video
    double dHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT);		//the height of frames of the video
    clog<<"Frame Size: "<<dWidth<<"x"<<dHeight<<endl;
    //init()
    Mat image;

    initControl();

    double ret[2] = {0, 0};
    while(true) {
        //图片处理
        capture>>image;
        if(image.empty()){break;}

        process_img(image,ret);
        process_box(image,ret);

        //小车控制
        cout << "left dis: " << ret[0] << " right dis: "<< ret[1] << endl;
        control(ret[0], ret[1]);
    }

    stopCar();
}
