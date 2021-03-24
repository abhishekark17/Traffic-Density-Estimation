#include "IO.hpp"

using namespace cv;
using namespace std;

vector<Point2f> inputPts;	// 4 pts taken from user to select the area of interest	//
vector<Point2f> Pts_dst;	// destination pts.	//
Mat imgGray; //backGroundground image displayed which will be used for selecting the four points//

//	taking input	//
void getPointsFromUser(int event, int x, int y, int flags, void* userData) {
	if (event == EVENT_LBUTTONDOWN) {
		imshow("Original Frame", imgGray);
		if (inputPts.size() < 4) inputPts.push_back(Point2f(x, y));
	}
}

Mat warp(Mat img) {
	//	resetting both vectors	//
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	Mat transformedGray;	// bird eye view of grayscale image: saved in memory	//
	Mat croppedImg;

	inputPts.clear();
	Pts_dst.clear();
	if (img.empty()) {
		cout << "Error: Image file is empty" << endl;
		return img;
	}


	int w = img.size().width, h = img.size().height; //	w = 1920 h = 1080	//
	Size size(w, h);	//	Input image resolution as checked by image properties also	//


	//	we take input as taken by Riju Ma'am, i.e top left point first and then in anti clockwise direction	//
	//	these points below for destination transformation are as given by Riju Ma'am on the Course Website	//

	Pts_dst.push_back(Point2f(472, 52));
	Pts_dst.push_back(Point2f(472, 830));
	Pts_dst.push_back(Point2f(800, 830));
	Pts_dst.push_back(Point2f(800, 52));


	//	Take Points as Input	//
	cvtColor(img, imgGray, COLOR_BGR2GRAY); //	rgb to grayscale	//
	imshow("Original Frame", imgGray);

	setMouseCallback("Original Frame", getPointsFromUser, &inputPts);	// take input
	waitKey(0);	//	wait for infinite time till user presses any key.

	//	Transform now!	//
	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);	// get homography matrix
	warpPerspective(imgGray, transformedGray, matrix, size);
	//resize(transformedGray, transformedGray, Size(), 0.5, 0.5);


	//	cropping	//
	Rect roi(Point2i(472,52), Point2i(800,830));	//rect structure for cropping
	croppedImg = transformedGray(roi);

	waitKey(0);
	return croppedImg;
}

Mat warpWithoutUserInput(Mat image){
	int w = image.size().width, h = image.size().height; //	w = 1920 h = 1080	//
	Size size(w, h);	//	Input image resolution as checked by image properties also	//
	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);
	warpPerspective(image, image, matrix, size);
	Rect roi(Point2i(472,52), Point2i(800,830));	//rect structure for cropping
	image = image(roi);
	return image;
}



void performOutput (int whitePixels1, int whitePixels2, int totalPixels, int frameNumber, ofstream& file) {
	float queueDensity = (float) whitePixels1 / (float) totalPixels;
	float dynamicDensity = (float) whitePixels2 / (float) totalPixels;

	file << frameNumber << "," << queueDensity << "," << dynamicDensity << "\n";
	cout << frameNumber << "," << dynamicDensity << "," << dynamicDensity << "\n";

	return;
}

void performOutputM1 (int whitePixels1,int whitePixels2,int totalPixels,int frameNumber,ofstream& file,int x) {
	float queueDensity = (float) whitePixels1 / (float) totalPixels;
	float dynamicDensity = (float) whitePixels2 / (float) totalPixels;

	for (int i = 0; i < x; i++) {
		file << (frameNumber + i)<< "," << queueDensity << "," << dynamicDensity << "\n";
		cout << frameNumber + i << "," << dynamicDensity << "," << dynamicDensity << "\n";
	}
	return;
}