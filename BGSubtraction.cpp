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
#include "BGSubtraction.hpp"

using namespace cv;
using namespace std;

Mat performBackgroundSubtraction (Mat& inputFrame, Mat& backGround) {
	Mat queueDensityImg;
	absdiff(inputFrame , backGround , queueDensityImg);
	threshold( queueDensityImg, queueDensityImg, 25, 255, THRESH_BINARY);
	return queueDensityImg;
}