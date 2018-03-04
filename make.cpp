///* Video is made my this file by compiling the all output images that

///* Dimension 300 X 450 .


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
using namespace cv;
// Namespace where all the C++ OpenCV functionality resides.

using namespace std;
// For input output operations.

//6
//8
//15
int main()
{
    VideoCapture in_capture("frame_result2%d.jpg");

    Mat img;


  VideoWriter out_capture("flicker_myresult.avi", CV_FOURCC('M','J','P','G'), 30, Size(450,300));

  while (true)
  {
    in_capture >> img;
    if(img.empty())
        break;

    out_capture.write(img);
  }
}
