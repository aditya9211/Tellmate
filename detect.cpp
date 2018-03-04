///* Writing the resulting frame to frame_result?.jpg
///* Threshold value of r +g +b is 225.
/* Border is marked with 3 pixels
    ThreshHold Area is 15 * Width of Image
                        i.e 15*150 = 2250
    Border of Detection is marked by TH value i.e 3.

    ThreshHold for Detection of pixels is sum of rgb <=225.
*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
using namespace cv;
// Namespace where all the C++ OpenCV functionality resides.
#define SF 45
#define TH 3
using namespace std;
// For input output operations.

//6
//8
//15
int main()
{

//int frame_count = 0;
VideoCapture cap("flicker.mp4");

  int frame_count = 0;
  bool should_stop = false;

  while(!should_stop)
  {
    Mat img;
    cap >> img; //get a new frame from the video
    if (img.empty())
    {
      should_stop = true; //we arrived to the end of the video
      continue;
    }

    char filename[128],filename2[128];
    sprintf(filename, "frame_result2%d.jpg", frame_count);
    sprintf(filename2, "Frame %d.jpg", frame_count);





//220 170

//Mat img = imread("frame_4.jpg");
///* Compression of input image ***//
resize(img, img, Size(150, 120), 0, 0, INTER_CUBIC);
Mat clo = img.clone();
resize(clo, clo, Size(150, 120), 0, 0, INTER_CUBIC);

///* Frame of output Image **//
Mat img1(300, 450, CV_8UC3, Scalar(255, 255, 255));
//resize(img1, img1, Size(520, 240), 0, 0, INTER_CUBIC);

int lft =-1;
int rght =-1;
int count=0;
int flag=0;

///** Code for the Detection of limits of Flickers Area ***///
for(int i=0; i<img.rows; i++){
    count=0;
    for(int j=0; j<img.cols; j++){
        // You can now access the pixel value with cv::Vec3b
        int r = (int)img.at<Vec3b>(i,j)[0];
        int g = (int)img.at<Vec3b>(i,j)[1];
        int b = (int)img.at<Vec3b>(i,j)[2];

      //  fprintf(fp,"%d ",r+g+b);

        ///* Threshold for detection of limit in rows
        if( r+g+b <= 225 && flag==0)
        {
            count++;
        }

        if (r+g+b > 225 && flag==1)
        {
            rght = i;
            flag = -1;
            break;
        }
    }
   // fprintf(fp,"\n");
    if(count==img.cols)
    {
       // printf("debug\n");
        flag = 1;
        lft = i;
    }

    if(flag==-1)
        break;
}

if( lft !=-1 && rght==-1)
    rght = img.rows-1;


///* Threshold for the area to be called as Flickering ***//
if(lft !=-1 && rght!=-1)
{
    if(abs(rght-lft) <= 15)
    {
        lft = rght = -1;
    }
}


///* Code for Making the Boundary with Red Color ***//
if( lft !=-1 && rght !=-1)
{
    for(int i=lft;i<=rght;i++)
    {
        if(i == lft + TH )
        {
            i = rght - TH ;
            continue;
        }
        for(int j=0;j<img.cols;j++)
        {
                clo.at<Vec3b>(i,j)[2] = 255;
                clo.at<Vec3b>(i,j)[1] = 0;
                clo.at<Vec3b>(i,j)[0] = 0;
        }
    }


    for(int i=lft;i<rght;i++)
    {
        int len = clo.cols;
        for(int k=0;k<TH;k++){
        clo.at<Vec3b>(i,k)[2] = 255;
        clo.at<Vec3b>(i,k)[1] = 0;
        clo.at<Vec3b>(i,k)[0] = 0;

        clo.at<Vec3b>(i,len-k-1)[2] = 255;
        clo.at<Vec3b>(i,len-k-1)[1] = 0;
        clo.at<Vec3b>(i,len-k-1)[0] = 0;
        }
    }
}
else
{
    for(int i=0;i< clo.rows;i++)
    {
        if(i == TH )
        {
            i = clo.rows - TH ;
            continue;
        }
        for(int j=0;j<img.cols;j++)
        {
                clo.at<Vec3b>(i,j)[2] = 255;
                clo.at<Vec3b>(i,j)[1] = 0;
                clo.at<Vec3b>(i,j)[0] = 0;
        }
    }

    for(int i=0;i< clo.rows;i++)
    {
        int len = clo.cols;
        for(int k=0;k<TH;k++){
        clo.at<Vec3b>(i,k)[2] = 255;
        clo.at<Vec3b>(i,k)[1] = 0;
        clo.at<Vec3b>(i,k)[0] = 0;

        clo.at<Vec3b>(i,len-k-1)[2] = 255;
        clo.at<Vec3b>(i,len-k-1)[1] = 0;
        clo.at<Vec3b>(i,len-k-1)[0] = 0;
        }
    }
}



//namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//imshow( "Display window", img1 );
//resizeWindow("Display window", 800,500);

///* Copying of two image in one container Image ***//

    Size sz1 = img.size();
    Size sz2 = clo.size();
   // Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
    Mat left(img1, Rect(100-SF, 90, sz1.width, sz1.height));
    img.copyTo(left);
    Mat right(img1, Rect(sz1.width + 140 -SF , 90, sz2.width, sz2.height));
    clo.copyTo(right);

   // putText(img1, "Differencing the two images.", cvPoint(280,30),
    //FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);

///* Inserting of  Text in Container Image **///

    putText(img1, filename2, cvPoint(140-SF ,80),
    FONT_HERSHEY_SIMPLEX, 0.3, cvScalar(0,0,0), 1.0, 15);

    if(lft !=-1 && rght!=-1)
    putText(img1, "Flickering Detected", cvPoint(170 + sz1.width-SF ,80),
    FONT_HERSHEY_SIMPLEX, 0.3, cvScalar(0,0,0), 1.0, 15);
    else
    putText(img1, "No Flickering Detected", cvPoint(160 + sz1.width -SF,80),
    FONT_HERSHEY_SIMPLEX, 0.3, cvScalar(0,0,0), 1.0, 15);


///* Comment area for Debugging Purposes ***//
//FONT_HERSHEY_COMPLEX_SMALL

// Resize src so that is has the same size as img
  //  resize(img1, img, img.size());
  //  resize(img, img1, Size(), 0.75, 0.75);

   // resize(img1, img1, Size(430, 320), 0, 0, INTER_CUBIC);
    //imshow("Display window", img1);




   // imwrite("aditya2.jpeg",img1);


   // waitKey(0);


  //  moveWindow("Display window", 270, 100);
      //  cout << (int)img.at<Vec3b>(60,300)[0] << " " << (int)img.at<Vec3b>(60,300)[1] << " " << (int)img.at<Vec3b>(60,300)[2] << endl;
//cvReleaseImage(&img);
//printf( "size x = %d , size y = %d\n",img.rows,img.cols);
//printf("l = %d , u= %d\n",lft,rght);
    /*img.release();
    img1.release();
    clo.release();
    left.release();
    right.release();*/



    imwrite(filename, img1);
    frame_count++;
    fflush(stdout);
  }

}
