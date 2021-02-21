#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
// Note:: All images that are read or written are assumed to be in the same directory as this file. We need to mention this in Readme file.	//


vector<Point2f> inputPts;	// 4 pts taken from user	//
vector<Point2f> Pts_dst;	// destination pts.	//

Mat img;		// input image	//
Mat imgGray;	// converted to grayscale	//
Mat transformedGray;	// bird eye view of grayscale image: saved in memory	//
Mat croppedImg;	//	final cropped image: also saved in memory

//	taking input	//
void getPointsFromUser(int event, int x, int y, int flags, void* userData) {
	if (event == EVENT_LBUTTONDOWN) {
		imshow("Original Frame", imgGray);
		if (inputPts.size() < 4) inputPts.push_back(Point2f(x, y));
	}
}



int main(int argc, char* argv[]) {
	//	resetting both vectors	//

	inputPts.clear();
	Pts_dst.clear();


	//	read image properly	//
	string path = "empty.jpg";
	img = imread(path);
	if (img.empty()) {
		cout << "Error: Image file is empty" << endl;
		return -1;
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
	resize(imgGray, imgGray, Size(), 0.5, 0.5);	//	fit/scale the window for user else very big	//
	imshow("Original Frame", imgGray);

	setMouseCallback("Original Frame", getPointsFromUser, &inputPts);	// take input
	waitKey(0);	//	wait for infinite time till user presses any key.


	//	Transform now!	//
	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);	// get homography matrix
	warpPerspective(imgGray, transformedGray, matrix, size);
	resize(transformedGray, transformedGray, Size(), 0.5, 0.5);


	//	cropping	//
	Rect roi(Point2i(240, 30), Point2i(400, 410));	//rect structure for cropping
	croppedImg = transformedGray(roi);


	//	show and write operations	//
	imshow("Projected Frame", transformedGray);
	imwrite("transformedEmpty.jpg", transformedGray);
	imshow("Cropped Frame", croppedImg);
	imwrite("croppedEmpty.jpg", croppedImg);
	waitKey(0);


	return 0;
}
