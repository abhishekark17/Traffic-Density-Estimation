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
#include "OpticalFlow.hpp"
#include "BGSubtraction.hpp"
#include "IO.hpp"

using namespace cv;
using namespace std;

void performSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength);
void performSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength,int x,int y);
void performSpecialSubtask2 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength, int beginFrame, int endFrame, int threadNumber); 
void performSubtask2M4 (Mat& backGround, VideoCapture& cap, ofstream& file, int queueLength, int topLeftX, int topLeftY, int w, int h, int threadNumber); 