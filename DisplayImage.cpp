#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

void converterParaCinza(Mat& image) {
    for(int x = 0; x < image.size().width; x++) {
        for(int y = 0; y < image.size().height; y++) {
            int blue  = image.at<Vec3b>(y, x)[0];
            int green = image.at<Vec3b>(y, x)[1];
            int red   = image.at<Vec3b>(y, x)[2];
            Vec<unsigned char, 3>& pixel = image.at<Vec3b>(Point(x, y));
            pixel[0] = pixel[1] = pixel[2] = blue * 0.114 + green * 0.587 + red * 0.229; // blue
        } 
    }
}

void converterParaCorInvertida(Mat& image) {
    for(int x = 0; x < image.size().width; x++) {
        for(int y = 0; y < image.size().height; y++) {
            Vec<unsigned char, 3>& pixel = image.at<Vec3b>(Point(x, y));
            pixel[0] = 255 - image.at<Vec3b>(y, x)[0]; // blue
            pixel[1] = 255 - image.at<Vec3b>(y, x)[1]; // green
            pixel[2] = 255 - image.at<Vec3b>(y, x)[2]; // red
        } 
    }
}

void converterParaLimiar(Mat& image, int limiar){
    for(int x = 0; x < image.size().width; x++) {
        for(int y = 0; y < image.size().height; y++) {
            if(image.at<Vec3b>(Point(x, y))[0] > limiar) {
                image.at<Vec3b>(Point(x, y))[0] = 1;
            } else {
                image.at<Vec3b>(Point(x, y))[0] = 0;
            }

            if(image.at<Vec3b>(Point(x, y))[1] > limiar) {
                image.at<Vec3b>(Point(x, y))[1] = 1;
            } else {
                image.at<Vec3b>(Point(x, y))[1] = 0;
            }

            if(image.at<Vec3b>(Point(x, y))[2] > limiar) {
                image.at<Vec3b>(Point(x, y))[2] = 1;
            } else {
                image.at<Vec3b>(Point(x, y))[2] = 0;
            }
        } 
    }
}


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    // converterParaCinza(image);
    converterParaCorInvertida(image);
    // converterParaLimiar(image, 50);

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);

    return 0;
}

