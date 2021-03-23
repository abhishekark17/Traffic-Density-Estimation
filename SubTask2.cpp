#include "SubTask2.hpp"

using namespace cv;
using namespace std;

void performSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength) {

    backGround = warp(backGround);
	int totalPixels = backGround.rows * backGround.cols;

    //const int queueLength = 5;
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
	int frameNumber = queueLength;    // we have wasted first 5 frames already 

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
    destroyAllWindows();
    return;
}