
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/video/tracking.hpp>

//  PLEASE NOTE  //
#include "mymain.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{	
	//	Initialize I/O	//
	String imagepath="images/emptyBackground.jpg";
	string videopath="video/trafficvideo.mp4";
	ofstream file("data.csv");	
	if (argc==1) cout<<"Video file should be given as argument"<<endl;
	else{
		string videoFileName=argv[1];
		videopath = "video/"+videoFileName;
	}
    VideoCapture cap(videopath);

	if (!cap.isOpened()) {
		cout << "Error: video file is empty" << endl;
		return -1;
	}
	
    //	backGround :: Fixed background for background subtraction for vehicular density	//
    Mat backGround = imread(imagepath);
    backGround = warp(backGround);
	int totalPixels = backGround.rows * backGround.cols;

	// previous :: First frame of the video to begin optical flow. Later on will be used as previous frame in while loop for optical flow	//
	
	const int queueLength = 5;
	queue<Mat> myQueue;
	for (int i = 0; i < queueLength; i++) {
		Mat temp;
		cap >> temp;
		cvtColor(temp,temp,COLOR_BGR2GRAY);
		temp = warpWithoutUserInput(temp);
		myQueue.push(temp);
	}
	
	Mat previous = myQueue.front();
	myQueue.pop();


	file<<"Frame,QueueDensity,DynamicDensity\n";
	cout<<"Frame,QueueDensity,DynamicDensity\n";
	int frameNumber=0;

    while(true){	
		Mat inputNextFrame; 
		cap >> inputNextFrame;// cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		//cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		if (inputNextFrame.empty()) break;
		frameNumber += 1;	//	taking every 5th frame - Ma'am said we can take every 3rd or 5th	//

		cvtColor(inputNextFrame, inputNextFrame, COLOR_BGR2GRAY);
		inputNextFrame = warpWithoutUserInput(inputNextFrame);
		myQueue.push(inputNextFrame);

		imshow("Original Video" , inputNextFrame);
		

		Mat queueDensityImg = performBackgroundSubtraction(inputNextFrame, backGround);
		Mat dynamicDensityImg = performOpticalFlow(previous, inputNextFrame);
		imshow("Background Subtraction Output" , queueDensityImg);
		imshow("Optical Flow Output" , dynamicDensityImg);

		int whitePixels1 = countNonZero(queueDensityImg);
		int whitePixels2= countNonZero(dynamicDensityImg);

		performOutput(whitePixels1, whitePixels2, totalPixels, frameNumber, file);
		
		int keyboard = waitKey(1);
        if (keyboard == 'q' || keyboard == 27) break;

		//previous = inputNextFrame;
		previous = myQueue.front();
		myQueue.pop();
    }
	file.close();
    destroyAllWindows();
    return 0;
}