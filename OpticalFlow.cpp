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


//   PLEASE NOTE   //
#include "OpticalFlow.hpp"

using namespace cv;
using namespace std;



Mat filterImage (Mat & img_bw) {
    //img_bw = img_bw > 5;

    // Define the structuring elements
    Mat se1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat se2 = getStructuringElement(MORPH_RECT, Size(5, 5));

    // Perform closing then opening
    Mat mask;
    morphologyEx(img_bw, mask, MORPH_CLOSE, se1);
    morphologyEx(mask, mask, MORPH_OPEN, se2);

    // Filter the output
    Mat out = mask.clone();
    out.setTo(Scalar(0), mask == 0);

	return out;
	//return mask;
}


Mat performOpticalFlow (Mat& previous, Mat& next ) {
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5)); 

	//	Define Optical flow parameters	//
	Mat flow(previous.size(), CV_32FC2);
	
    calcOpticalFlowFarneback(previous, next, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
	
	// For visualization	//
    Mat flow_parts[2];
    split(flow, flow_parts);
    Mat magnitude, angle, magn_norm;
    cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
    normalize(magnitude, magn_norm, 0.0f, 1.0f, NORM_MINMAX);
    angle *= ((1.f / 360.f) * (180.f / 255.f));

	//	To build hsv image	//
    Mat _hsv[3], hsv, hsv8, bgr;
	Mat opticalFlowOutput;
    _hsv[0] = angle;
    _hsv[1] = Mat::ones(angle.size(), CV_32F);
    _hsv[2] = magn_norm;
    merge(_hsv, 3, hsv);
    hsv.convertTo(hsv8, CV_8U, 255.0);
	cvtColor(hsv8, bgr, COLOR_HSV2BGR);
	cvtColor(bgr, opticalFlowOutput, COLOR_BGR2GRAY);

	//	To process the optical flow output and remove noise	//
	
	opticalFlowOutput = filterImage(opticalFlowOutput);
	morphologyEx(opticalFlowOutput, opticalFlowOutput,MORPH_RECT, kernel);
	threshold( opticalFlowOutput, opticalFlowOutput, 12 ,255,THRESH_BINARY);
	return opticalFlowOutput;
}







