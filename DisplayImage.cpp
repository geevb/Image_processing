#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

Mat converterParaCinza(Mat image) {
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < newImage.size().height; y++) {
        for(int x = 0; x < newImage.size().width; x++) {
            Vec<unsigned char, 3>& oldImagePixel = image.at<Vec3b>(Point(x, y));  
            Vec<unsigned char, 3>& pixel = newImage.at<Vec3b>(Point(x, y));

            pixel[0] = pixel[1] = pixel[2] = oldImagePixel[0] * 0.114 + oldImagePixel[1] * 0.587 + oldImagePixel[2] * 0.229; // blue
        } 
    }

    return newImage;
}

Mat converterParaCorInvertida(Mat image) {
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < newImage.size().height; y++) {
        for(int x = 0; x < newImage.size().width; x++) {
            Vec<unsigned char, 3>& oldImagePixel = image.at<Vec3b>(Point(x, y));       
            Vec<unsigned char, 3>& newImagePixel = newImage.at<Vec3b>(Point(x, y));

            newImagePixel[0] = 255 - oldImagePixel[0]; // blue
            newImagePixel[1] = 255 - oldImagePixel[1]; // green
            newImagePixel[2] = 255 - oldImagePixel[2]; // red
        } 
    }

    return newImage;
}

// TODO: REVISAR
Mat converterParaLimiar(Mat image, int limiar) {
    Mat newImage;
    image.copyTo(newImage);
    for(int y = 0; y < newImage.size().height; y++) {
        for(int x = 0; x < newImage.size().width; x++) {
            Vec<unsigned char, 3>& pixel = newImage.at<Vec3b>(Point(x, y));
            if(pixel[0] > limiar) {
                pixel[0] = 0;
            } else {
                pixel[0] = 255;
            }

            if(pixel[1] > limiar) {
                pixel[1] = 0;
            } else {
                pixel[1] = 255;
            }

            if(pixel[2] > limiar) {
                pixel[2] = 0;
            } else {
                pixel[2] = 255;
            }
        } 
    }

    return newImage;
}

Mat isolarCanalDeCor(std::string cor, Mat image) {
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < image.size().height; y++) {
        for(int x = 0; x < image.size().width; x++) {
            Vec<unsigned char, 3>& oldImagePixel = image.at<Vec3b>(Point(x, y));       
            Vec<unsigned char, 3>& newImagePixel = newImage.at<Vec3b>(Point(x, y));

            if(cor == "B") {
                newImagePixel[0] = oldImagePixel[0];
                newImagePixel[1] = newImagePixel[2] = 0;
            }

            if(cor == "G") {
                newImagePixel[1] = oldImagePixel[1];
                newImagePixel[0] = newImagePixel[2] = 0;
            }

            if(cor == "R") {
                newImagePixel[2] = oldImagePixel[2];
                newImagePixel[0] = newImagePixel[1] = 0;
            }

        }
    }

    return newImage;
}

Mat incrementarCanaisDeDor(std::string cor, int tipo, int valor, Mat image) {
    // Tipo 0: Inteiro, 1: Percentual
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < image.size().height; y++) {
        for(int x = 0; x < image.size().width; x++) {
            Vec<unsigned char, 3>& oldImagePixel = image.at<Vec3b>(Point(x, y));       
            Vec<unsigned char, 3>& newImagePixel = newImage.at<Vec3b>(Point(x, y));

            if(cor == "B") {
                double novoValor = (tipo == 0) ? oldImagePixel[0] + valor : ( oldImagePixel[0] + (oldImagePixel[0] * (valor / 100)));
                newImagePixel[0] = (novoValor <= 255) ? novoValor : 255;
                newImagePixel[1] = oldImagePixel[1];
                newImagePixel[2] = oldImagePixel[2];
            }
            
            if(cor == "G") {
                double novoValor = (tipo == 0) ? oldImagePixel[1] + valor : ( oldImagePixel[1] + (oldImagePixel[1] * (valor / 100)));
                newImagePixel[0] = oldImagePixel[0]; 
                newImagePixel[1] = (novoValor <= 255) ? novoValor : 255;
                newImagePixel[2] = oldImagePixel[2];
            }

            if(cor == "R") {
                double novoValor = (tipo == 0) ? oldImagePixel[2] + valor : ( oldImagePixel[2] + (oldImagePixel[2] * (valor / 100)));
                newImagePixel[0] = oldImagePixel[0];
                newImagePixel[1] = oldImagePixel[1];
                newImagePixel[2] = (novoValor > 255) ? 255 : novoValor;
            }
        }      
    }

    return newImage;
}

Mat zoomIn(int zoomValue, Mat image) {
    if (zoomValue == 1) return image;

    Mat newImage(image.size().height * zoomValue, image.size().width * zoomValue, CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < newImage.size().height; y += zoomValue) {
        for(int x = 0; x < newImage.size().width; x += zoomValue ) {
            Vec<unsigned char, 3>& oldImagePixel = image.at<Vec3b>(Point(x, y));       
            Vec<unsigned char, 3>& newImagePixel = newImage.at<Vec3b>(Point(x, y));

            for(int z = 0; z < zoomValue; z++) {
                for(int w = 0; w < zoomValue; w ++) {
                    newImage.at<Vec3b>(Point(z, w)) = image.at<Vec3b>(Point(x, y));
                }
                // newImage.at<Vec3b>(Point(x, y));
                // y0x0m, y0x1, y1x0, y1x1
            }

        }
    }

    return newImage;
}

Mat somarImagem(Mat img1, Mat img2) {
    int height = (img1.size().height > img2.size().height) ? img1.size().height : img2.size().height;
    int width  = (img1.size().width > img2.size().width) ? img1.size().width : img2.size().width;
    Mat newImg(height, width, CV_8UC3, Scalar(255, 255, 255));
    for(int y = 0; y < newImg.size().height; y++) {
        for(int x = 0; x < newImg.size().width; x++) {
            Vec<unsigned char, 3>& newImgPixel = newImg.at<Vec3b>(Point(x, y));
            Vec<unsigned char, 3>& pxlImg1 = img1.at<Vec3b>(Point(x, y));
            Vec<unsigned char, 3>& pxlImg2 = img2.at<Vec3b>(Point(x, y));
            if(x > img1.size().width || y > img1.size().height ||
               x > img2.size().width || y > img2.size().height) 
            {
                newImgPixel[0] = newImgPixel[1] = newImgPixel[2] = 255;
                continue;
            }

            int add0 = pxlImg1[0] + pxlImg2[0];
            int add1 = pxlImg1[1] + pxlImg2[1];
            int add2 = pxlImg1[2] + pxlImg2[2];
            newImgPixel[0] = (add0 > 255) ? 255 : add0;
            newImgPixel[1] = (add1 > 255) ? 255 : add1;
            newImgPixel[2] = (add2 > 255) ? 255 : add2;
        }
    }

    return newImg;
}

Mat subtrairImagem(Mat imgMinuendo, Mat imgSubtraendo) {
    Mat newImg(imgMinuendo.size().height, imgMinuendo.size().width, CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < newImg.size().height; y++) {
        for(int x = 0; x < newImg.size().width; x++) {
            Vec<unsigned char, 3>& newImgPixel = newImg.at<Vec3b>(Point(x, y));
            Vec<unsigned char, 3>& pxlMinuendo = imgMinuendo.at<Vec3b>(Point(x, y));
            Vec<unsigned char, 3>& pxlSubtraendo = imgSubtraendo.at<Vec3b>(Point(x, y));
            if(x > imgSubtraendo.size().width || y > imgSubtraendo.size().height) {
                newImgPixel[0] = pxlMinuendo[0];
                newImgPixel[1] = pxlMinuendo[1];
                newImgPixel[2] = pxlMinuendo[2];
                continue;
            }

            int sub0 = pxlMinuendo[0] - pxlSubtraendo[0];
            int sub1 = pxlMinuendo[1] - pxlSubtraendo[1];
            int sub2 = pxlMinuendo[2] - pxlSubtraendo[2];
            newImgPixel[0] = (sub0 < 0) ? 0 : sub0;
            newImgPixel[1] = (sub1 < 0) ? 0 : sub1;
            newImgPixel[2] = (sub2 < 0) ? 0 : sub2;
        }
    }
    
    return newImg;
}


void menuInicial() {
    std::cout <<"    ____  _       _ __        __   ____                         "      << std::endl;
    std::cout <<"   / __ \\(_)___ _(_) /_____ _/ /  /  _/___ ___  ____ _____ ____ "     << std::endl;
    std::cout <<"  / / / / / __ `/ / __/ __ `/ /   / // __ `__ \\/ __ `/ __ `/ _ \\"    << std::endl;
    std::cout <<" / /_/ / / /_/ / / /_/ /_/ / /  _/ // / / / / / /_/ / /_/ /  __/"      << std::endl;
    std::cout <<"/_____/_/\\__, /_/\\__/\\__,_/_/  /___/_/ /_/ /_/\\__,_/\\__, /\\___/ "<< std::endl;
    std::cout <<"        /____/                                     /____/       "      << std::endl;
    std::cout <<"                           .---."              << std::endl;
    std::cout <<"                           |[X]|"              << std::endl;
    std::cout <<"                    _.==._.\"\"\"\"\".___n__"  << std::endl;
    std::cout <<"                   d __ ___.-\'\'-. _____b "   << std::endl;
    std::cout <<"                   |[__]  /.\"\"\"\".\\     |" << std::endl;
    std::cout <<"                   |     // /\"\"\\ \\\\    |" << std::endl;
    std::cout <<"                   |     \\\\ \\__/ //    |"   << std::endl;
    std::cout <<"                   |pentax\\`.__.\'/     |"    << std::endl;
    std::cout <<"                   \\=======`-..-\'======/"    << std::endl;
    std::cout <<"                    `-----------------\' "     << std::endl;
    std::cout <<"       ____                                 _            "    << std::endl;
    std::cout <<"      / __ \\_________  ________  __________(_)___  ____ _"   << std::endl;
    std::cout <<"     / /_/ / ___/ __ \\/ ___/ _ \\/ ___/ ___/ / __ \\/ __ `/" << std::endl;
    std::cout <<"    / ____/ /  / /_/ / /__/  __(__  |__  ) / / / / /_/ / "    << std::endl;
    std::cout <<"   /_/   /_/   \\____/\\___/\\___/____/____/_/_/ /_/\\__, /  "<< std::endl;
    std::cout <<"                                                /____/   "    << std::endl;

 
}

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



    // Mat transformedImage = converterParaCinza(image);
    // Mat transformedImage = converterParaCorInvertida(image);
    // Mat transformedImage = converterParaLimiar(image, 50);
    // Mat transformedImage = isolarCanalDeCor("R", image);
    // Mat transformedImage = incrementarCanaisDeDor("R", 0, 255, image);
    // Mat transformedImage = zoomIn(2, image);
    // Mat transformedImage = subtrairImagem(image, image2);
    // Mat transformedImage = somarImagem(image, image2);
    menuInicial();


    namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", transformedImage);
    waitKey(0);

    return 0;
}

