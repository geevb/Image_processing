#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
using namespace cv;

Mat converterParaCinzaMedia(Mat image) {
    Mat newImage(image.rows, image.cols, CV_8UC3, Scalar(0,0,0));
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelOld;
    int height = newImage.size().height;
    int width = newImage.size().width;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImage.ptr<Vec3b>(y);
        ptrPixelOld = image.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            ptrPixelNew[x][0] = ptrPixelNew[x][1] = ptrPixelNew[x][2] = (ptrPixelOld[x][0] + ptrPixelOld[x][1] + ptrPixelOld[x][2]) / 3;
        } 
    }

    return newImage;
}



Mat converterParaCinzaPonderado(Mat image) {
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelOld;
    int height = newImage.size().height;
    int width = newImage.size().width;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImage.ptr<Vec3b>(y);
        ptrPixelOld = image.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            ptrPixelNew[x][0] = ptrPixelNew[x][1] = ptrPixelNew[x][2] = ptrPixelOld[x][0] * 0.114 + ptrPixelOld[x][1] * 0.587 + ptrPixelOld[x][2] * 0.229;
        } 
    }

    return newImage;
}

Mat dilatar(Mat image, int limiar) {
    Mat newImage(image.rows, image.cols, CV_8UC3, Scalar(0,0,0));
    Mat oldImage = converterParaCinzaPonderado(image);
    threshold(oldImage, oldImage, limiar, 255, 0);
    int height = oldImage.size().height - 1;
    int width = newImage.size().width -1;
    for(int y = 1; y < height; y++) {
        for(int x = 1; x < width; x++) {
            Vec<unsigned char, 3> oldImagePixel = oldImage.at<Vec3b>(Point(x, y));  
            Vec<unsigned char, 3>& pixel = newImage.at<Vec3b>(Point(x, y));

            if(oldImagePixel[0] == 255 && oldImagePixel[1] == 255 && oldImagePixel[2] == 255){
                for(int z = 0; z < 3; z++) {
                    newImage.at<Vec3b>(Point(x -1, y -1))[z] = 255;
                    newImage.at<Vec3b>(Point(x, y -1))[z] = 255;
                    newImage.at<Vec3b>(Point(x +1, y -1))[z] = 255;
                    newImage.at<Vec3b>(Point(x -1, y))[z] = 255;
                    newImage.at<Vec3b>(Point(x +1, y))[z] = 255;
                    newImage.at<Vec3b>(Point(x -1, y +1))[z] = 255;
                    newImage.at<Vec3b>(Point(x, y +1))[z] = 255;
                    newImage.at<Vec3b>(Point(x +1, y+1))[z] = 255;
                }
            }
        } 
    }

    return newImage;
}

bool deveErodir(int x, int y, Mat &oldImage) {
    return  oldImage.at<Vec3b>(Point(x -1, y -1))[0] == 255 && // POS: 0,0
            oldImage.at<Vec3b>(Point(x -1, y))[0] == 255 &&    // POS: 0,1
            oldImage.at<Vec3b>(Point(x -1, y +1))[0] == 255 && // POS: 0,2
            oldImage.at<Vec3b>(Point(x, y -1))[0] == 255 &&    // POS: 1,0
            oldImage.at<Vec3b>(Point(x, y +1))[0] == 255 &&    // POS: 1,2
            oldImage.at<Vec3b>(Point(x +1, y -1))[0] == 255 && // POS: 2,0
            oldImage.at<Vec3b>(Point(x +1, y))[0] == 255 &&    // POS: 2,1
            oldImage.at<Vec3b>(Point(x +1, y +1))[0] == 255;   // POS: 2,2
}

// bool deveErodir(int x, int y, Mat &oldImage) {
//     Vec3b* ptr = oldImage.ptr<Vec3b>(y);
//     return  ptr[x] -1, y -1))[0] == 255 && // POS: 0,0
//             ptr[x] -1, y))[0] == 255 &&    // POS: 0,1
//             ptr[x] -1, y +1))[0] == 255 && // POS: 0,2
//             ptr[x], y -1))[0] == 255 &&    // POS: 1,0
//             ptr[x], y +1))[0] == 255 &&    // POS: 1,2
//             ptr[x] +1, y -1))[0] == 255 && // POS: 2,0
//             ptr[x] +1, y))[0] == 255 &&    // POS: 2,1
//             ptr[x] +1, y +1))[0] == 255;   // POS: 2,2
// }

Mat erodir(Mat image, int limiar) {
    Mat newImage(image.rows, image.cols, CV_8UC3, Scalar(0,0,0));
    Mat oldImage = converterParaCinzaPonderado(image);
    threshold(oldImage, oldImage, limiar, 255, 0);
    int height = oldImage.rows - 1;
    int width = oldImage.cols -1;
    for(int y = 1; y < height; y++) {

        Vec3b* pixel = oldImage.ptr<Vec3b>(y);
        for(int x = 1; x < width; x++) {
            // Vec<unsigned char, 3>& pixel = newImage.at<Vec3b>(Point(x, y));
            pixel[x];
            if(deveErodir(x, y, oldImage)) {
                pixel[x][0] = pixel[x][1] = pixel[x][2] = 255;
            }
        } 
    }

    return newImage;
}

int presentHistogram(Mat image) {
    std::vector<int> histRed(256, 0);
    std::vector<int> histGreen(256, 0);
    std::vector<int> histBlue(256, 0);
    
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            Vec<unsigned char, 3>& pixels = image.at<Vec3b>(Point(x, y));

            histRed.insert(histRed.begin() + pixels[0], pixels[0] + 1);
            histGreen.insert(histGreen.begin() + pixels[0], pixels[0] + 1);
            histBlue.insert(histBlue.begin() + pixels[0], pixels[0] + 1);
        }
    }

    int sizeRed, sizeBlue, sizeGreen = 0;
    for(int x = 0; x < 256; x++) {
        if(histRed.at(x) < sizeRed) {
            sizeRed = histRed.at(x);
        }

        if(histBlue.at(x) < sizeBlue) {
            sizeBlue = histBlue.at(x);
        }

        if(histGreen.at(x) < sizeGreen) {
            sizeGreen = histGreen.at(x);
        }
    }

    Mat HistPlotR (sizeRed, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat HistPlotG (sizeBlue, 256, CV_8UC3, Scalar(0, 0, 0));
    Mat HistPlotB (sizeGreen, 256, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < 256; i++) {
        line(HistPlotR, Point(i, 500), Point(i, 500-histRed[i]  ), Scalar(0, 0, 255), 1, 8, 0);
        line(HistPlotG, Point(i, 500), Point(i, 500-histGreen[i]), Scalar(0, 255, 0), 1, 8, 0);
        line(HistPlotB, Point(i, 500), Point(i, 500-histBlue[i] ), Scalar(255, 0, 0), 1, 8, 0);
    }

    namedWindow("Red Histogram", cv::WINDOW_AUTOSIZE);
    namedWindow("Green Histogram", cv::WINDOW_AUTOSIZE);
    namedWindow("Blue Histogram", cv::WINDOW_AUTOSIZE);
    imshow("Red Histogram", HistPlotR);
    imshow("Green Histogram", HistPlotG);
    imshow("Blue Histogram", HistPlotB);
    return 0;
}

int showHistogram(Mat image) {
  std::vector<Mat> bgr_planes;
  split( image, bgr_planes );

  int histSize = 256;

  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;

  Mat b_hist, g_hist, r_hist;

  calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

  int hist_w = 900; int hist_h = 800;
  int bin_w = cvRound( (double) hist_w/histSize );

  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
  }

  namedWindow("Histogram", CV_WINDOW_AUTOSIZE );
  imshow("Histogram", histImage );

  return 0;
}

Mat converterParaCorInvertida(Mat image) {
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    int height = newImage.size().height;
    int width = newImage.size().width;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelOld;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImage.ptr<Vec3b>(y);
        ptrPixelOld = image.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            ptrPixelNew[x][0] = 255 - ptrPixelOld[x][0]; // blue
            ptrPixelNew[x][1] = 255 - ptrPixelOld[x][1]; // green
            ptrPixelNew[x][2] = 255 - ptrPixelOld[x][2]; // red
        } 
    }

    return newImage;
}

Mat limiarizar(Mat image, int limiar) {
    Mat grayImage = converterParaCinzaPonderado(image);
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    int height = newImage.size().height;
    int width = newImage.size().width;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelGray;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImage.ptr<Vec3b>(y);
        ptrPixelGray = grayImage.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            ptrPixelNew[x][0] = ptrPixelNew[x][1] =  ptrPixelNew[x][2] = (ptrPixelGray[x][0] > limiar) ? 255 : 0;
        }
    }

    return newImage;
}

Mat isolarCanalDeCor(std::string cor, Mat image) {
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    int height = newImage.size().height;
    int width = newImage.size().width;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelOld;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImage.ptr<Vec3b>(y);
        ptrPixelOld = image.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            if(cor == "B") {
                ptrPixelNew[x][0] = ptrPixelOld[x][0];
                ptrPixelNew[x][1] = ptrPixelNew[x][2] = 0;
            }

            if(cor == "G") {
                ptrPixelNew[x][1] = ptrPixelOld[x][1];
                ptrPixelNew[x][0] = ptrPixelNew[x][2] = 0;
            }

            if(cor == "R") {
                ptrPixelNew[x][2] = ptrPixelOld[x][2];
                ptrPixelNew[x][0] = ptrPixelNew[x][1] = 0;
            }

        }
    }

    return newImage;
}

Mat incrementarCanaisDeDor(std::string cor, int tipo, int valor, Mat image) {
    // Tipo 1: Inteiro, 2: Percentual
    Mat newImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    int height = newImage.size().height;
    int width = newImage.size().width;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelOld;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImage.ptr<Vec3b>(y);
        ptrPixelOld = image.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            if(cor == "B") {
                double novoValor = (tipo == 1) ? ptrPixelOld[x][0] + valor : ( ptrPixelOld[x][0] + (ptrPixelOld[x][0] * (valor / 100)));
                ptrPixelNew[x][0] = (novoValor <= 255) ? novoValor : 255;
                ptrPixelNew[x][1] = ptrPixelOld[x][1];
                ptrPixelNew[x][2] = ptrPixelOld[x][2];
            }
            
            if(cor == "G") {
                double novoValor = (tipo == 1) ? ptrPixelOld[x][1] + valor : ( ptrPixelOld[x][1] + (ptrPixelOld[x][1] * (valor / 100)));
                ptrPixelNew[x][0] = ptrPixelOld[x][0]; 
                ptrPixelNew[x][1] = (novoValor <= 255) ? novoValor : 255;
                ptrPixelNew[x][2] = ptrPixelOld[x][2];
            }

            if(cor == "R") {
                double novoValor = (tipo == 1) ? ptrPixelOld[x][2] + valor : ( ptrPixelOld[x][2] + (ptrPixelOld[x][2] * (valor / 100)));
                ptrPixelNew[x][0] = ptrPixelOld[x][0];
                ptrPixelNew[x][1] = ptrPixelOld[x][1];
                ptrPixelNew[x][2] = (novoValor > 255) ? 255 : novoValor;
            }
        }      
    }

    return newImage;
}

Mat zoomIn(int zoomValue, Mat image) {
    if (zoomValue <= 1) return image;

    Mat newImage(image.size().height * zoomValue, image.size().width * zoomValue, CV_8UC3, Scalar(0,0,0));
    int height = image.size().height;
    int width = image.size().width;
    Vec3b* ptrPixelOld;
    for(int y = 0; y < height; y++) {
        ptrPixelOld = image.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            newImage.ptr<Vec3b>(y * zoomValue)[x * zoomValue] = ptrPixelOld[x];
            newImage.ptr<Vec3b>(y * zoomValue)[x * zoomValue +1] = ptrPixelOld[x];
            newImage.ptr<Vec3b>(y * zoomValue +1)[x * zoomValue] = ptrPixelOld[x];
            newImage.ptr<Vec3b>(y * zoomValue +1)[x * zoomValue +1] = ptrPixelOld[x];
        }
    }

    return newImage;
}

Mat zoomOut(int zoomValue, Mat image) {
    if (zoomValue <= 1) return image;
    
    double zoomOut = 1 / zoomValue;
    Mat newImage(image.size().height * zoomValue, image.size().width * zoomValue, CV_8UC3, Scalar(0,0,0));
    Mat resizedImage(image.size().height, image.size().width, CV_8UC3, Scalar(0,0,0));
    int height = image.size().height;
    int width = image.size().width;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            Vec<unsigned char, 3>& oldImagePixel = image.at<Vec3b>(Point(x, y));       
            Vec<unsigned char, 3>& newImagePixel = newImage.at<Vec3b>(Point(x, y));

            newImage.at<Vec3b>(Point(x * zoomValue   , y * zoomValue)) = oldImagePixel;
            newImage.at<Vec3b>(Point(x * zoomValue +1, y * zoomValue)) = oldImagePixel;
            newImage.at<Vec3b>(Point(x * zoomValue   , y * zoomValue +1)) = oldImagePixel;
            newImage.at<Vec3b>(Point(x * zoomValue +1, y * zoomValue +1)) = oldImagePixel;
        }
    }
    // TODO corrigir
    cv::resize(image, resizedImage, cv::Size(), 0.75, 0.75);
    return resizedImage;
}


Mat somarImagem(Mat img1, Mat img2) {
    int totalHeight = (img1.size().height < img2.size().height) ? img1.size().height : img2.size().height;
    int totalWidth  = (img1.size().width < img2.size().width) ? img1.size().width : img2.size().width;
    Mat newImg(totalHeight, totalWidth, CV_8UC3, Scalar(255, 255, 255));
    int height = newImg.size().height;
    int width = newImg.size().width;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelImg1;
    Vec3b* ptrPixelImg2;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImg.ptr<Vec3b>(y);
        ptrPixelImg1 = img1.ptr<Vec3b>(y);
        ptrPixelImg2 = img2.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            int add0 = ptrPixelImg1[x][0] + ptrPixelImg2[x][0];
            int add1 = ptrPixelImg1[x][1] + ptrPixelImg2[x][1];
            int add2 = ptrPixelImg1[x][2] + ptrPixelImg2[x][2];
            ptrPixelNew[x][0] = (add0 > 255) ? 255 : add0;
            ptrPixelNew[x][1] = (add1 > 255) ? 255 : add1;
            ptrPixelNew[x][2] = (add2 > 255) ? 255 : add2;
        }
    }

    return newImg;
}



Mat somarImagemPonderada(Mat img1, Mat img2, int percentImg1, int percentImg2) {
    int totalHeight = (img1.size().height < img2.size().height) ? img1.size().height : img2.size().height;
    int totalWidth  = (img1.size().width < img2.size().width) ? img1.size().width : img2.size().width;
    Mat newImg(totalHeight, totalWidth, CV_8UC3, Scalar(255, 255, 255));
    int height = newImg.size().height;
    int width = newImg.size().width;
    double porcentagem1 = (double) percentImg1 / 100;
    double porcentagem2 = (double) percentImg2 / 100;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelImg1;
    Vec3b* ptrPixelImg2;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImg.ptr<Vec3b>(y);
        ptrPixelImg1 = img1.ptr<Vec3b>(y);
        ptrPixelImg2 = img2.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            if(x > img1.size().width || y > img1.size().height ||
               x > img2.size().width || y > img2.size().height) 
            {
                ptrPixelNew[x][0] = ptrPixelNew[x][1] = ptrPixelNew[x][2] = 255;
                continue;
            }

            int add0 = round((double) ptrPixelImg1[x][0] * porcentagem1 + (double) ptrPixelImg2[x][0] * porcentagem2);
            int add1 = round((double) ptrPixelImg1[x][1] * porcentagem1 + (double) ptrPixelImg2[x][1] * porcentagem2);
            int add2 = round((double) ptrPixelImg1[x][2] * porcentagem1 + (double) ptrPixelImg2[x][2] * porcentagem2);

            ptrPixelNew[x][0] = (add0 > 255) ? 255 : add0;
            ptrPixelNew[x][1] = (add1 > 255) ? 255 : add1;
            ptrPixelNew[x][2] = (add2 > 255) ? 255 : add2;
        }
    }

    return newImg;
}


Mat subtrairImagem(Mat imgMinuendo, Mat imgSubtraendo) {
    int totalHeight = (imgMinuendo.size().height < imgSubtraendo.size().height) ? imgMinuendo.size().height : imgSubtraendo.size().height;
    int totalWidth  = (imgMinuendo.size().width < imgSubtraendo.size().width) ? imgMinuendo.size().width : imgSubtraendo.size().width;
    Mat newImg(totalHeight, totalWidth, CV_8UC3, Scalar(0,0,0));
    int height = newImg.size().height;
    int width = newImg.size().width;
    Vec3b* ptrPixelNew;
    Vec3b* ptrPixelImgMinuendo;
    Vec3b* ptrPixelImgSubtraendo;
    for(int y = 0; y < height; y++) {
        ptrPixelNew = newImg.ptr<Vec3b>(y);
        ptrPixelImgMinuendo = imgMinuendo.ptr<Vec3b>(y);
        ptrPixelImgSubtraendo = imgSubtraendo.ptr<Vec3b>(y);
        for(int x = 0; x < width; x++) {
            if(x > imgSubtraendo.size().width || y > imgSubtraendo.size().height) {
                ptrPixelNew[x][0] = ptrPixelImgMinuendo[x][0];
                ptrPixelNew[x][1] = ptrPixelImgMinuendo[x][1];
                ptrPixelNew[x][2] = ptrPixelImgMinuendo[x][2];
                continue;
            }

            int sub0 = ptrPixelImgMinuendo[x][0] - ptrPixelImgSubtraendo[x][0];
            int sub1 = ptrPixelImgMinuendo[x][1] - ptrPixelImgSubtraendo[x][1];
            int sub2 = ptrPixelImgMinuendo[x][2] - ptrPixelImgSubtraendo[x][2];
            ptrPixelNew[x][0] = (sub0 < 0) ? 0 : sub0;
            ptrPixelNew[x][1] = (sub1 < 0) ? 0 : sub1;
            ptrPixelNew[x][2] = (sub2 < 0) ? 0 : sub2;
        }
    }
    
    return newImg;
}
