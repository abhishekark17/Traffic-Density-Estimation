#include <iostream>
#include <queue>
#include <thread>
#include <fstream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/video/tracking.hpp>

//  PLEASE NOTE  //

#include "OpticalFlow.hpp"
#include "BGSubtraction.hpp"
#include "IO.hpp"
#include "SubTask2.hpp"

using namespace cv;
using namespace std;
void workForEachThreadM4 (string videoPath, Mat backGround,int queueLength,int topLeftX, int topLeftY, int w, int h,int threadNumber,int totalthreads);
void performMethod4 (string& videoPath, Mat backGround,int queueLength, int numThreads);

