#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include "control.cpp"
using namespace cv;

//EFICIENCIA
// for(int i = 0; i < img.rows; ++i)
// {
//     // get pointers to each row
//     cv::Vec3b* row = img.ptr<cv::Vec3b>(i);

//     // now scan the row
//     for(int j = 0; j < img.cols; ++j)
//     {   
//         cv::Vec3b pixel = row[j];
//         uchar r = pixel[2];
//         uchar g = pixel[1];
//         uchar b = pixel[0];
//         process(r, g, b);
//     } 
// }



int main(int argc, char** argv )
{
    fluxo();

    // int mouseParam = CV_EVENT_FLAG_LBUTTON;
    // cvSetMouseCallback("Display Image",mouseHandler,&mouseParam);

    return 0;
}

