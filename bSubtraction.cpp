#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    String path="video/main3.mp4";
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(2, 3));
    //create Background Subtractor objects
    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorMOG2();
    VideoCapture capture(path);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video"<< endl;
        return 0;
    }
    Mat frame, fgMask;
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;
        //update the background model
        pBackSub->apply(frame, fgMask);
        //get the frame number and write it on the current frame
        rectangle(frame, Point(10, 2), Point(100,20),
                  Scalar(255,255,255), -1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
        //show the current frame and the fg masks
        morphologyEx(fgMask, fgMask,MORPH_OPEN, kernel);
        imshow("Frame", frame);
        imshow("FG Mask", fgMask);
        //get the input from the keyboard
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }
    return 0;
}