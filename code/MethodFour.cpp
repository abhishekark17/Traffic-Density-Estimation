#include "MethodFour.hpp"

using namespace cv;
using namespace std;


void workForEachThreadM4 (string videoPath, Mat backGround,int queueLength,int topLeftX, int topLeftY, int w, int h,int threadNumber,int totalthreads) {
    VideoCapture cap (videoPath);
    ofstream file("../analysis/data/data4/dataM4N" +to_string(totalthreads) +"T"+ to_string(threadNumber)+".csv");	
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

    int heightPerThread = bgHeight / numThreads;
    int tempTopLeftX = 0, tempTopLeftY = 0;

    vector<thread> allThreads;

    for (int i = 1; i <= numThreads; i++) {
        allThreads.push_back(thread(workForEachThreadM4, videoPath,backGround,queueLength,tempTopLeftX,tempTopLeftY,bgWidth,heightPerThread,i,numThreads));

        if (i == numThreads - 1) {
            tempTopLeftY += heightPerThread;
            heightPerThread = bgHeight - tempTopLeftY;
        }
        else tempTopLeftY += heightPerThread;
        
    }

    for (auto & x : allThreads) if (x.joinable()) x.join();
    return;

    // depending upon the number of threads it is possible that the spatial distribution of pixels
    // is not the same for the last thread (any remaining non divisible columns of image will be pushed for the last thread) 
}