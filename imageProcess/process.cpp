#include <cstdlib>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define CV_SHOW_FINAL
//#define CV_DEBUG
#define PI_I 3.1415926

const string CAM_PATH="/dev/video0";
const string MAIN_WINDOW_NAME="Processed Image";
const string CANNY_WINDOW_NAME="Canny";

//canny的上下界
const int CANNY_LOWER_BOUND=50;
const int CANNY_UPPER_BOUND=250;

//hough检测的线段长度阈值
const int HOUGH_THRESHOLD=40;

//resize后的大小
const int Resized_Width = 512;
const int Resized_Height = 512;

//灰度阈值
const double Grey_Threshold = 100;
const int Max_Binary_Val = 255;
const int Binary_Threshold_Type = 0;

//hough检测的线段长度阈值
const int BOX_HOUGH_THRESHOLD=50;

//erode和dilate卷积核
const Mat BOX_Conv_Kernel = getStructuringElement(MORPH_RECT, Size(10,10));

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
    HoughLines(contours,lines,1,PI_I/180,HOUGH_THRESHOLD);
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
#ifdef CV_SHOW_FINAL
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
#ifdef CV_SHOW_FINAL
            line(x,pt1,pt2,Scalar(0,255,255),3,CV_AA);
            cout<<pt1<<pt2<<endl;
#endif
            is_right= true;
        }
    }

    double mid  = img.cols/2;
    ret[0] = mid-left_down.x;
    if(left_down.x==0){ret[0]=2*mid;}
    ret[1] = right_down.x>0?right_down.x-mid:2*mid;
    cout<<"左距离 "<< ret[0]<<"  右距离 "<<ret[1]<<endl;
    imshow(MAIN_WINDOW_NAME,x);
    //waitKey(1);
}

/**
 * 处理图片
 * */


void my_box_dilate_and_erode(Mat& src, Mat& tar){
    dilate(tar,tar,BOX_Conv_Kernel);
    erode(tar, tar, BOX_Conv_Kernel);

}



void detect_box(Mat& x, Mat& img, double ret[]){
    int mid = img.cols/2;

    Mat contours;
    Canny(img,contours,CANNY_LOWER_BOUND,CANNY_UPPER_BOUND);
#ifdef CV_DEBUG
    // imshow(CANNY_WINDOW_NAME,contours);
#endif

    vector<Vec2f> lines;
    HoughLines(contours,lines,1,PI_I/180,35);
    Mat result(img.size(),CV_8U,Scalar(255));
    img.copyTo(result);

#ifdef CV_DEBUG
    cout<<"lines: ";
    cout<<lines.size()<<endl;
#endif

    Point2f left_down;
    Point2f left_up;
    int left_lines = 0;
    for(vector<Vec2f>::const_iterator it=lines.begin();it!=lines.end();++it)
    {
        float rho=(*it)[0];			//First element is distance rho
        float theta=(*it)[1];		//Second element is angle theta
        //(theta>0 && theta<1 )||(theta>1.57&&theta<1.8)
        if(theta>0 && theta<0.5) {
            cout<<rho<<" "<<theta<<endl;
            Point pt1(rho/cos(theta),0);
            left_up = pt1;
            //point of intersection of the line with last row
            Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
            left_down = pt2;
            //Draw a line
            line(x,pt1,pt2,Scalar(0,255,255),3,CV_AA);
            cout<<pt1<<pt2<<endl;
            if (left_down.x < mid){left_lines++;}
            if(left_down.x > mid){left_lines--;}
        }
    }
    if (left_lines>0){
//        if (ret[0]==2*mid){ret[0]= }
        ret[0] -= mid;
    }
    if (left_lines<0){ret[1] -= mid;}
    imshow(MAIN_WINDOW_NAME,x);
}


void RemoveSmallRegion(Mat &Src, Mat &Dst,int AreaLimit, int CheckMode, int NeihborMode)
{
    int RemoveCount = 0;
    //新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查
    //初始化的图像全部为0，未检查
    Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
    if (CheckMode == 1)//去除小连通区域的白色点
    {
        cout << "去除小连通域.";
        for (int i = 0; i < Src.rows; i++)
        {
            for (int j = 0; j < Src.cols; j++)
            {
                if (Src.at<uchar>(i, j) < 10)
                {
                    PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3
                }
            }
        }
    }
    else//去除孔洞，黑色点像素
    {
        cout << "去除孔洞";
        for (int i = 0; i < Src.rows; i++)
        {
            for (int j = 0; j < Src.cols; j++)
            {
                if (Src.at<uchar>(i, j) > 10)
                {
                    PointLabel.at<uchar>(i, j) = 3;//如果原图是白色区域，标记为合格，像素为3
                }
            }
        }
    }


    vector<Point2i>NeihborPos;//将邻域压进容器
    NeihborPos.push_back(Point2i(-1, 0));
    NeihborPos.push_back(Point2i(1, 0));
    NeihborPos.push_back(Point2i(0, -1));
    NeihborPos.push_back(Point2i(0, 1));
    if (NeihborMode == 1)
    {
        cout << "Neighbor mode: 8邻域." << endl;
        NeihborPos.push_back(Point2i(-1, -1));
        NeihborPos.push_back(Point2i(-1, 1));
        NeihborPos.push_back(Point2i(1, -1));
        NeihborPos.push_back(Point2i(1, 1));
    }
    else cout << "Neighbor mode: 4邻域." << endl;
    int NeihborCount = 4 + 4 * NeihborMode;
    int CurrX = 0, CurrY = 0;
    //开始检测
    for (int i = 0; i < Src.rows; i++)
    {
        for (int j = 0; j < Src.cols; j++)
        {
            if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点
            {   //开始检查
                vector<Point2i>GrowBuffer;//记录检查像素点的个数
                GrowBuffer.push_back(Point2i(j, i));
                PointLabel.at<uchar>(i, j) = 1;//标记为正在检查
                int CheckResult = 0;


                for (int z = 0; z < GrowBuffer.size(); z++)
                {
                    for (int q = 0; q < NeihborCount; q++)
                    {
                        CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
                        CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
                        if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界
                        {
                            if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
                            {
                                GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer
                                PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查
                            }
                        }
                    }
                }
                if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出
                    CheckResult = 2;
                else
                {
                    CheckResult = 1;
                    RemoveCount++;//记录有多少区域被去除
                }


                for (int z = 0; z < GrowBuffer.size(); z++)
                {
                    CurrX = GrowBuffer.at(z).x;
                    CurrY = GrowBuffer.at(z).y;
                    PointLabel.at<uchar>(CurrY,CurrX)+=CheckResult;//标记不合格的像素点，像素值为2
                }
                //********结束该点处的检查**********


            }
        }


    }


    CheckMode = 255 * (1 - CheckMode);
    //开始反转面积过小的区域
    for (int i = 0; i < Src.rows; ++i)
    {
        for (int j = 0; j < Src.cols; ++j)
        {
            if (PointLabel.at<uchar>(i,j)==2)
            {
                Dst.at<uchar>(i, j) = CheckMode;
            }
            else if (PointLabel.at<uchar>(i, j) == 3)
            {
                Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);

            }
        }
    }
    cout << RemoveCount << " objects removed." << endl;
}


void process_box(Mat& img, double ret[]){
    Mat tmp = img;

    Rect roi = Rect(0, 0, tmp.cols, tmp.rows);
    tmp = Mat(tmp, roi);
    img = tmp;


    Mat imgHSV, red1, red2;
    cvtColor(tmp, imgHSV, COLOR_BGR2HSV);
    inRange(imgHSV, Scalar(0,43,35), Scalar(11,255,255), red1);
    inRange(imgHSV, Scalar(155,43,35), Scalar(180,255,255), red2);
    imgHSV = red1+red2;
    imgHSV = 255 - imgHSV;
    imshow("red", imgHSV);
//    RemoveSmallRegion(imgHSV, imgHSV, 100, 0, 0);
    tmp = imgHSV;
    my_box_dilate_and_erode(tmp, tmp);
//    GaussianBlur(tmp, tmp, Size(10,10),0,0);
    detect_box(img, tmp, ret);
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
    Mat grey = tmp;
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

#ifdef CV_DEBUG
    imshow("shrink", tmp);
#endif

    detect_lines(x, tmp, ret);
//    detect_box(x, grey, ret);
}


