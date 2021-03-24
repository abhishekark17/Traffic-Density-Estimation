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

void workForEachThread (string videoPath, Mat backGround,int queueLength, int beginFrame, int endFrame, int threadNumber);
void performMethod5 (string& videoPath, Mat& backGround,int queueLength, int numThreads);
