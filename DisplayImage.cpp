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
    // if ( argc != 2 )
    // {
    //     printf("usage: DisplayImage.out <Image_Path>\n");
    //     return -1;
    // }

    // Mat image;
    // image = imread( argv[1], 1 );

    // Mat image2;
    // image2 = imread("white.png");
    // if ( !image.data || !image2.data )
    // {
    //     printf("No image data \n");
    //     return -1;
    // }

    fluxo();


    // Mat transformedImage = converterParaCinza(image);
    // Mat transformedImage = converterParaCorInvertida(image);
    // Mat transformedImage = converterParaLimiar(image, 50);
    // Mat transformedImage = isolarCanalDeCor("R", image);
    // Mat transformedImage = incrementarCanaisDeDor("R", 0, 255, image);
    // Mat transformedImage = zoomIn(2, image);
    // Mat transformedImage = subtrairImagem(image, image2);
    // Mat transformedImage = somarImagem(image, image2);
    // menuInicial();
    // showHistogram(image);
    // makeHistogramCsv(image);
    // presentHistogram(image);
    // openWebcam();
    // Mat transformedImage = limiarizar(image, 150);
    // Mat transformedImage = zoomIn(3, image);

    // int mouseParam = CV_EVENT_FLAG_LBUTTON;

    // namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", transformedImage);
    // cvSetMouseCallback("Display Image",mouseHandler,&mouseParam);
    // waitKey(0);

    return 0;
}

