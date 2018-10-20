#include <cstdlib>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define CV_DEBUG
#define PI 3.1415926

const string CAM_PATH="/dev/video0";
const string MAIN_WINDOW_NAME="Processed Image";
const string CANNY_WINDOW_NAME="Canny";

//canny的上下界
const int CANNY_LOWER_BOUND=50;
const int CANNY_UPPER_BOUND=250;

//hough检测的线段长度阈值
const int HOUGH_THRESHOLD=70;

//resize后的大小
const int Resized_Width = 512;
const int Resized_Height = 512;

//灰度阈值
const double Grey_Threshold = 100;
const int Max_Binary_Val = 255;
const int Binary_Threshold_Type = 0;

//erode和dilate卷积核
const Mat Conv_Kernel = getStructuringElement(MORPH_RECT, Size(10,10));

//缩小
void my_shrink(Mat& src, Mat& tar){
    resize(src, tar, Size(src.cols/2, Resized_Height), 0, 0,  INTER_LINEAR);
}

//切割roi
void my_crop(Mat& src, Mat& tar){
    //crop
    Rect roi = Rect(0, src.rows/3, src.cols, src.rows/3);
    tar = Mat(src, roi);
}

//灰度处理
void my_grey(Mat& src, Mat& tar){
    cvtColor(src, tar, COLOR_BGR2GRAY);
    threshold(tar, tar, Grey_Threshold, Max_Binary_Val, Binary_Threshold_Type);
}

/*
 * 膨胀+腐蚀
 * */
void my_dilate_and_erode(Mat& src, Mat& tar){
    erode(tar, tar, Conv_Kernel);
    dilate(src, tar, Conv_Kernel);
}

/**
 * 反色
 * */
void my_inverse(Mat& src, Mat& tar){
    tar = 255-src;
}

/**
 * 模糊平滑化
 * */
void my_smooth(Mat& src, Mat& tar){
    medianBlur(src, tar, 7);
}

/**
 * 检测直线
 * */
void detect_lines(Mat& x,Mat& img, double ret[]){
    Mat contours;
    Canny(img,contours,CANNY_LOWER_BOUND,CANNY_UPPER_BOUND);
#ifdef CV_DEBUG
    imshow(CANNY_WINDOW_NAME,contours);
#endif

    vector<Vec2f> lines;
    HoughLines(contours,lines,1,PI/180,HOUGH_THRESHOLD);
    Mat result(img.size(),CV_8U,Scalar(255));
    img.copyTo(result);

#ifdef CV_DEBUG
    cout<<"lines: ";
    cout<<lines.size()<<endl;
#endif

    Point2f left_down;
    Point2f right_down;
    Point2f left_up;
    Point2f right_up;
    bool  is_left = false;
    bool is_right = false;
    //Draw the lines and judge the slope
    for(vector<Vec2f>::const_iterator it=lines.begin();it!=lines.end();++it)
    {
        float rho=(*it)[0];			//First element is distance rho
        float theta=(*it)[1];		//Second element is angle theta
        cout<<rho<<" "<<theta<<endl;

        if(!is_left&&theta>0&&theta<1.37)
        {
            //point of intersection of the line with first row
            Point pt1(rho/cos(theta),0);
            left_up = pt1;
            //point of intersection of the line with last row
            Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
            left_down = pt2;
            //Draw a line
#ifdef CV_DEBUG
            line(x,pt1,pt2,Scalar(0,255,255),3,CV_AA);
            cout<<pt1<<pt2<<endl;
#endif
            is_left= true;
        }
        if (!is_right&&theta>1.8&&theta<3.14){
            //point of intersection of the line with first row
            Point pt1(rho/cos(theta),0);
            right_up = pt1;
            //point of intersection of the line with last row
            Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
            right_down = pt2;
            //Draw a line
#ifdef CV_DEBUG
            line(x,pt1,pt2,Scalar(0,255,255),3,CV_AA);
            cout<<pt1<<pt2<<endl;
#endif
            is_right= true;
        }
    }

    double mid  = img.cols/2;
    ret[0] = mid-left_down.x;
    ret[1] = right_down.x>0?right_down.x-mid:mid;

    imshow(MAIN_WINDOW_NAME,x);
}

/**
 * 处理图片
 * */
void process_img(Mat& img, double ret[]){
    Mat tmp = img;
    imshow("origin", img);

//    my_shrink(img, tmp);
//    imshow("shrink", tmp);

    my_crop(tmp, tmp);
#ifdef CV_DEBUG
    imshow("crop", tmp);
#endif

    Mat x = tmp;

    my_grey(tmp, tmp);
#ifdef CV_DEBUG
    imshow("grey", tmp);
#endif

    my_dilate_and_erode(tmp, tmp);
#ifdef CV_DEBUG
    imshow("dilate and erode", tmp);
#endif

    my_inverse(tmp, tmp);
#ifdef CV_DEBUG
    imshow("inverse", tmp);
#endif

    my_smooth(tmp, tmp);
#ifdef CV_DEBUG
    imshow("smooth", tmp);
#endif

    my_shrink(tmp, tmp);
#ifdef CV_DEBUG
    imshow("shrink", tmp);
#endif

    detect_lines(x, tmp, ret);
    if(ret[0]<0){ret[1]+=-ret[0];}
    if(ret[1]<0){ret[0]+=-ret[1];}
}
