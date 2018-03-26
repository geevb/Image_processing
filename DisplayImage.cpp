#include "control.cpp"

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



int main() {

    // while(true) {
        fluxo();
        // if (perguntarDesejaIniciarNovamente() != 1) break;
        // int mouseParam = CV_EVENT_FLAG_LBUTTON;
        // cvSetMouseCallback("Display Image",mouseHandler,&mouseParam);
    // }
    return 0;
}

