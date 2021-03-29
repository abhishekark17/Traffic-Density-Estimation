#include "MethodOne.hpp"

using namespace cv;
using namespace std;

/*
    Please note that the first queueLength number of frames will not be in the output data as they are removed for optical flow

    After the Nth frame, N+x th frame will be processed and pushed into the queue. 
    Hence x-1 frames in between will be dropped.

    Assumption: Larger the value of x, Lesser the RunTime and Higher the error.
*/
void performMethod1 (Mat& backGround, VideoCapture& cap, ofstream& file,  int queueLength, int x) {
    //backGround = warp(backGround);
	cvtColor(backGround,backGround,COLOR_BGR2GRAY);
	backGround = warpWithoutUserInput(backGround);
	int totalPixels = backGround.rows * backGround.cols;

	queue<Mat> myQueue;
    // for example if queueLength = 4 and x = 5, then the frames that will be pushed into the queue will be [1, 6, 11, 16] only
	for (int i = 0; i < queueLength; i++) {
		Mat temp;
        if (i == 0) cap >> temp;
        else for (int j = 0; j < x; j++) cap >> temp;
		
		cvtColor(temp,temp,COLOR_BGR2GRAY);
		temp = warpWithoutUserInput(temp);
		myQueue.push(temp);
	}
	
	Mat previous = myQueue.front();
	myQueue.pop();


	file<<"Frame,QueueDensity,DynamicDensity\n";
	cout<<"Frame,QueueDensity,DynamicDensity\n";
	int frameNumber = 1 +  (queueLength-1)*x;    // 16 = 1 + (4-1) * 5 

    while(true){	
		Mat inputNextFrame; 
        // if frameNumber was N, now we have N+x th frame in inputNextFrame
        for (int i = 0; i < x; i++) cap >> inputNextFrame;  // 21 st frame
		
		
		if (inputNextFrame.empty()) break;
		frameNumber += x;	// 21 = 16 + 5

		cvtColor(inputNextFrame, inputNextFrame, COLOR_BGR2GRAY);
		inputNextFrame = warpWithoutUserInput(inputNextFrame);
		myQueue.push(inputNextFrame);

		imshow("Original Video (skipping every " + to_string(x-1) + " frames)" , inputNextFrame);
		

		Mat queueDensityImg = performBackgroundSubtraction(inputNextFrame, backGround);
		Mat dynamicDensityImg = performOpticalFlow(previous, inputNextFrame);
		imshow("Background Subtraction Output" , queueDensityImg);
		imshow("Optical Flow Output" , dynamicDensityImg);

		int whitePixels1 = countNonZero(queueDensityImg);
		int whitePixels2= countNonZero(dynamicDensityImg);

		//performOutput(whitePixels1, whitePixels2, totalPixels, frameNumber, file);
		//for (int i = 1; i < x; i++) performOutput(whitePixels1,whitePixels2,totalPixels,frameNumber + i,file);
        performOutputM1(whitePixels1,whitePixels2,totalPixels,frameNumber,file, x);

		int keyboard = waitKey(1);
        if (keyboard == 'q' || keyboard == 27) break;

		//previous = inputNextFrame;
		previous = myQueue.front();
		myQueue.pop();
    }
    destroyAllWindows();
    return;
}

