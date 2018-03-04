///* Used to convert the given video to different
///* frame and saving them in same Directory
///*    by this code


#include <stdio.h>
#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
// Namespace where all the C++ OpenCV functionality resides.

using namespace std;
int main( )
{

    printf("* Filename: %s\n", "flicker.mp4");

    CvCapture *capture = cvCaptureFromAVI("flicker_result.avi");
    if(!capture)
    {
        printf("!!! cvCaptureFromAVI failed (file not found?)\n");
        return -1;
    }

    int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    printf("* FPS: %d\n", fps);

    IplImage* frame = NULL;
    int frame_number = 0;
    char key = 0;

    while (key != 'q')
    {
        // get frame
        frame = cvQueryFrame(capture);
        if (!frame)
        {
            printf("!!! cvQueryFrame failed: no frame\n");
            break;
        }

        char filename[100];
        strcpy(filename, "frameres_");

        char frame_id[30];
        itoa(frame_number, frame_id, 10);
        strcat(filename, frame_id);
        strcat(filename, ".jpg");

        printf("* Saving: %s\n", filename);

        if (!cvSaveImage(filename, frame))
        {
            printf("!!! cvSaveImage failed\n");
            break;
        }

        frame_number++;

        // quit when user press 'q'
        key = cvWaitKey(1000 / fps);
    }

    // free resources
    cvReleaseCapture(&capture);

    return 0;
}
