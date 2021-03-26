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

#include "OpticalFlow.hpp"
#include "BGSubtraction.hpp"
#include "IO.hpp"

using namespace cv;
using namespace std;

void performMethod1 (Mat& backGround, VideoCapture& cap, ofstream& file,  int queueLength, int x) ;

