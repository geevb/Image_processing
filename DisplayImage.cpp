#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
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
    // namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", image);
    // waitKey(0);
    
    for(int x = 0; x < image.size().width; x++) {
        for(int y = 0; y < image.size().height; y++) {
            Vec3b intensity = image.at<Vec3b>(y, x);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            std::cout << +blue << std::endl;
            std::cout << +green << std::endl;
            std::cout << +red << std::endl;
        } 
    }


    return 0;
}
