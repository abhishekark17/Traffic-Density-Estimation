#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Point2f> inputPts;	// 4 pts taken from user
vector<Point2f> Pts_dst;	// destination pts.

Mat img;		// input image
Mat imgGray;	// converted to grayscale
Mat transformedGray;	// bird eye view of grayscale image

// taking input
void getPointsFromUser(int event, int x, int y, int flags, void * userData) {
	if (event == EVENT_LBUTTONDOWN) {
		imshow("Greyed Image", imgGray);
		if (inputPts.size() < 4) inputPts.push_back(Point2f(x, y));
	}
}



int main(int argc, char* argv[]) {
	// resetting both vectors
	inputPts.clear();
	Pts_dst.clear();		


	// read image properly
	string path = "empty.jpg";
	Mat img = imread(path);		
	if (img.empty()) {
		cout << "Error: Image file is empty" << endl;
		return -1;
	} 

		
	int w = img.size().width, h = img.size().height; // w = 1920 h = 1080
	//int w = 250, h = 350;
	Size size(w, h);	// Destination size?? not clear as of now. hit and trial??

	// we take input as taken by Riju Ma'am, i.e top left first and then anti clockwise direction
	Pts_dst.push_back(Point2f(0, 0));
	Pts_dst.push_back(Point2f(0, h-1));
	Pts_dst.push_back(Point2f(w-1, h-1));
	Pts_dst.push_back(Point2f(w-1, 0));

	
	
	cvtColor(img, imgGray, COLOR_BGR2GRAY); // rgb to grayscale
	resize(imgGray, imgGray, Size(), 0.5, 0.5);	// fit/scale the window for user else very big
	imshow("Greyed Image", imgGray);
	
	setMouseCallback("Greyed Image", getPointsFromUser, &inputPts);	// take input

	waitKey(0);

	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);	// get homography matrix

	warpPerspective(imgGray, transformedGray, matrix,size);		
	resize(transformedGray, transformedGray, Size(), 0.5, 0.5);
	imshow("top view", transformedGray);
	waitKey(0);

	
	return 0;
}
