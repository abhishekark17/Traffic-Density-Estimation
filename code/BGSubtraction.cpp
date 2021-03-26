#include "BGSubtraction.hpp"

using namespace cv;
using namespace std;

Mat performBackgroundSubtraction (Mat& inputFrame, Mat& backGround) {
	Mat queueDensityImg;
	absdiff(inputFrame , backGround , queueDensityImg);
	threshold( queueDensityImg, queueDensityImg, 25, 255, THRESH_BINARY);
	return queueDensityImg;
}