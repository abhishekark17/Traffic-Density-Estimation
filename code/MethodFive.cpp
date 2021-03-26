#include "MethodFive.hpp"

using namespace cv;
using namespace std;

void workForEachThread (string videoPath, Mat backGround,int queueLength, int beginFrame, int endFrame, int threadNumber) {
    VideoCapture cap (videoPath);
    ofstream file("../analysis/data/dataM5T" + to_string(threadNumber)+ ".csv");	
	if (!cap.isOpened()) {
		cout << "Error: video file is empty" << endl;
		return;
	}

    performSpecialSubtask2(backGround,cap,file,queueLength,beginFrame,endFrame,threadNumber);

    file.close();
    return;
}

void performMethod5 (string& videoPath, Mat& backGround,int queueLength, int numThreads) {
    
    VideoCapture cap(videoPath);
    int totalFrames = cap.get(CAP_PROP_FRAME_COUNT);//  Getting the total number of frames    //
    cap.release();

    // depending upon number of threads, we separate the video into different parts.
    // since totalFrames maynot be exactly divisible by numThreads, hence the remaining extra threads
    // will be given to the last thread only. For example, suppose we have 100 frames and 6 threads,
    // then 16 frames will be given to each of the first 5 threads and 20 to the last thread.

    int framesPerThread = totalFrames/numThreads;   // 100/6 = 16
    int remainingFrames = totalFrames % numThreads; // 100 % 6 = 4
    int beginFrame = 0;
    int endFrame = framesPerThread;
    vector<thread> allThreads;
    
    for (int i = 1; i <= numThreads; i++) {
        //thread myTd (& workForEachThread, videoPath,backGround,queueLength,beginFrame,endFrame, i);
        //allThreads.push_back(myTd);
        allThreads.push_back(thread(workForEachThread, videoPath,backGround,queueLength,beginFrame,endFrame, i));
        beginFrame += framesPerThread;
        if (i == numThreads - 1) endFrame = totalFrames;
        else endFrame += framesPerThread;
    }

    for (auto & x : allThreads) if (x.joinable()) x.join();
    return;
}