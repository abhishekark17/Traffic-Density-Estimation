#include "MethodFour.hpp"

using namespace cv;
using namespace std;


void workForEachThreadM4 (string videoPath, Mat backGround,int queueLength,int topLeftX, int topLeftY, int w, int h,int threadNumber) {
    VideoCapture cap (videoPath);
    ofstream file("dataM4T" + to_string(threadNumber)+ ".csv");	
	if (!cap.isOpened()) {
		cout << "Error: video file is empty" << endl;
		return;
	}

    performSubtask2M4(backGround,cap,file,queueLength,topLeftX,topLeftY,w,h,threadNumber);

    file.close();
    return;
}

void performMethod4 (string& videoPath, Mat backGround,int queueLength, int numThreads) {

    backGround = warp(backGround);
    Size sz = backGround.size();
    int bgWidth = sz.width;
    int bgHeight = sz.height;

    int widthPerThread = bgWidth / numThreads;
    int tempTopLeftX = 0, tempTopLeftY = 0;

    vector<thread> allThreads;

    for (int i = 1; i <= numThreads; i++) {
        allThreads.push_back(thread(workForEachThreadM4, videoPath,backGround,queueLength,tempTopLeftX,tempTopLeftY,widthPerThread,bgHeight,i));

        if (i == numThreads - 1) {
            tempTopLeftX += widthPerThread;
            widthPerThread = bgWidth - tempTopLeftX;
        }
        else tempTopLeftX += widthPerThread;
        
    }

    for (auto & x : allThreads) if (x.joinable()) x.join();
    return;

    // depending upon the number of threads it is possible that the spatial distribution of pixels
    // is not the same for the last thread (any remaining non divisible columns of image will be pushed for the last thread) 
}