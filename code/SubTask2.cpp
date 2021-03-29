#include "SubTask2.hpp"

using namespace cv;
using namespace std;

void performSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength) {

    //backGround = warpSpecial(backGround);
	cvtColor(backGround,backGround,COLOR_BGR2GRAY);
	backGround = warpWithoutUserInput(backGround);
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

void performSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength,int x, int y) {

    //backGround = warp(backGround,x,y);
	cvtColor(backGround,backGround,COLOR_BGR2GRAY);
	backGround = warpWithoutUserInput(backGround,x,y);
	int totalPixels = backGround.rows * backGround.cols;

    //const int queueLength = 5;
	queue<Mat> myQueue;
	for (int i = 0; i < queueLength; i++) {
		Mat temp;
		cap >> temp;
		Size size(x,y);
		resize(temp,temp,size,0,0,INTER_LINEAR);
		cvtColor(temp,temp,COLOR_BGR2GRAY);
		temp = warpWithoutUserInput(temp,x,y);
		myQueue.push(temp);
	}
	
	Mat previous = myQueue.front();
	myQueue.pop();


	file<<"Frame,QueueDensity,DynamicDensity\n";
	cout<<"Frame,QueueDensity,DynamicDensity\n";
	int frameNumber = queueLength;    // we have wasted first 5 frames already 

    while(true){	
		Mat inputNextFrame; 
		Size size(x,y);
		cap >> inputNextFrame;// cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		//cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		if (inputNextFrame.empty()) break;
		resize(inputNextFrame,inputNextFrame,size,0,0,INTER_LINEAR);
		frameNumber += 1;	//	taking every 5th frame - Ma'am said we can take every 3rd or 5th	//

		cvtColor(inputNextFrame, inputNextFrame, COLOR_BGR2GRAY);
		inputNextFrame = warpWithoutUserInput(inputNextFrame,x,y);
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
// for method 5
void performSpecialSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength, int beginFrame, int endFrame, int threadNumber) {

    //backGround = warp(backGround);
	cvtColor(backGround,backGround,COLOR_BGR2GRAY);
	backGround=warpWithoutUserInput(backGround);
	int totalPixels = backGround.rows * backGround.cols;
	//CAP_PROP_POS_FRAMES 
	cap.set(CAP_PROP_POS_FRAMES, max(0,beginFrame - queueLength));
	
	
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
	int frameNumber = max (queueLength,beginFrame);    // we have wasted first 5 frames already 

    while(frameNumber < endFrame) {	
		Mat inputNextFrame; 
		cap >> inputNextFrame;// cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		//cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		if (inputNextFrame.empty()) break;
		frameNumber += 1;	//	taking every 5th frame - Ma'am said we can take every 3rd or 5th	//

		cvtColor(inputNextFrame, inputNextFrame, COLOR_BGR2GRAY);
		inputNextFrame = warpWithoutUserInput(inputNextFrame);
		myQueue.push(inputNextFrame);

		//imshow("Original Video of thread " + to_string(threadNumber) , inputNextFrame);
		

		Mat queueDensityImg = performBackgroundSubtraction(inputNextFrame, backGround);
		Mat dynamicDensityImg = performOpticalFlow(previous, inputNextFrame);
		imshow("Background Subtraction Output of thread " + to_string(threadNumber) , queueDensityImg);
		//imshow("Optical Flow Output of thread " + to_string(threadNumber) , dynamicDensityImg);

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

// 	FOR METHOD 4
void performSubtask2M4 (Mat backGround, VideoCapture& cap, ofstream& file, int queueLength, int topLeftX, int topLeftY, int w, int h, int threadNumber) {

    //backGround = warp(backGround);
	//cvtColor(backGround,backGround,COLOR_BGR2GRAY);
	//backGround = warpWithoutUserInput(backGround);
	int totalPixels = backGround.rows * backGround.cols;

	const Rect cropRegion (topLeftX, topLeftY, w,h);
    Mat bgCropped = backGround(cropRegion);

	

    //const int queueLength = 5;
	queue<Mat> myQueue;
	for (int i = 0; i < queueLength; i++) {
		Mat temp;
		cap >> temp;
		cvtColor(temp,temp,COLOR_BGR2GRAY);
		temp = warpWithoutUserInput(temp);
		temp = temp (cropRegion);
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
		inputNextFrame = inputNextFrame(cropRegion);
		myQueue.push(inputNextFrame);

		//imshow("Original Video of thread " + to_string(threadNumber) , inputNextFrame);
		

		Mat queueDensityImg = performBackgroundSubtraction(inputNextFrame, bgCropped);
		Mat dynamicDensityImg = performOpticalFlow(previous, inputNextFrame);
		imshow("Background Subtraction Output of thread " + to_string(threadNumber) , queueDensityImg);
		//imshow("Optical Flow Output of thread " + to_string(threadNumber) , dynamicDensityImg);

		int whitePixels1 = countNonZero(queueDensityImg);
		int whitePixels2= countNonZero(dynamicDensityImg);

		// 	NOTE HERE THAT WE ARE DIVIDING HERE BY TOTALPIXELS AND NOT PIXELS OF CROPPED IMAGE SO THAT LATER ON WHILE CALCULATING 
		// FINAL DENSITY OF WHOLE IMAGE, WE JUST NEED TO ADD UP COLUMNS PRODUCED BY DIFFERENT THREADS.
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