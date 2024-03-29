#include "IO.hpp"

using namespace cv;
using namespace std;

vector<Point2f> inputPts;	// 4 pts taken from user to select the area of interest	//
vector<Point2f> Pts_dst;	// destination pts.	//
vector<Point2f> inputPts_scaled;
vector<Point2f> Pts_dest_scaled;
Mat imgGray; //backGroundground image displayed which will be used for selecting the four points//

void initializeInputPts (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	inputPts.clear();
	inputPts.push_back(Point2f(x1,y1));
	inputPts.push_back(Point2f(x2,y2));
	inputPts.push_back(Point2f(x3,y3));
	inputPts.push_back(Point2f(x4,y4));
	return;
}
void initializeDestPts () {
	Pts_dst.clear();
	Pts_dst.push_back(Point2f(472, 52));
	Pts_dst.push_back(Point2f(472, 830));
	Pts_dst.push_back(Point2f(800, 830));
	Pts_dst.push_back(Point2f(800, 52));
	return;
}
void initializeInputPtsScaled (int x, int y) {
	inputPts_scaled.clear();
	float scale=(float)1920/(float)(x);
	float scale1=(float)1080/(float)(y);

	for (auto pt : inputPts) inputPts_scaled.push_back(Point2f((int)((float)pt.x/scale), (int)((float)pt.y/scale1)));
	return;
}
void initializeDestPtsScaled (int x, int y) {
	Pts_dest_scaled.clear();
	float scale=(float)1920/(float)(x);
	float scale1=(float)1080/(float)(y);
	Pts_dest_scaled.push_back(Point2f((int)((float)472/scale), (int)((float)52/scale1)));
	Pts_dest_scaled.push_back(Point2f((int)((float)472/scale), (int)((float)830/scale1)));
	Pts_dest_scaled.push_back(Point2f((int)((float)800/scale), (int)((float)830/scale1)));
	Pts_dest_scaled.push_back(Point2f((int)((float)800/scale), (int)((float)52/scale1)));
	return;
}

//	taking input	//
void getPointsFromUser(int event, int x, int y, int flags, void* userData) {
	if (event == EVENT_LBUTTONDOWN) {
		imshow("Original Frame", imgGray);
		if (inputPts.size() < 4) inputPts.push_back(Point2f(x, y));
	}
}
/*
Mat finalWarp (Mat img) {
	int w = img.size().width, h = img.size().height; //	w = 1920 h = 1080	//
	Size size(w, h);

	Mat transformedGray;
	Mat croppedImg;
	Mat imgGrey;
	cvtColor(img, imgGrey, COLOR_BGR2GRAY); //	rgb to grayscale	//
	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);	// get homography matrix
	warpPerspective(imgGrey, transformedGray, matrix, size);

	Rect roi(Point2i(472,52), Point2i(800,830));	//rect structure for cropping
	croppedImg = transformedGray(roi);
	return croppedImg;
}*/

Mat warp(Mat img) {
	//	resetting both vectors	//
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	Mat transformedGray;	// bird eye view of grayscale image: saved in memory	//
	Mat croppedImg;

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
	// hard code input points 
	/*
	inputPts.push_back(Point2f(996,210));
	inputPts.push_back(Point2f(415,1007));
	inputPts.push_back(Point2f(1545,1008));
	inputPts.push_back(Point2f(1282,223));
*/


/* commented out previous code to take input of points
	imshow("Original Frame", imgGray);
	setMouseCallback("Original Frame", getPointsFromUser, &inputPts);	// take input
	waitKey(0);	//	wait for infinite time till user presses any key.
*/


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

Mat warpSpecial (Mat img) {
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
	destroyWindow("Original Frame");


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

//For change in Resolutiion
Mat warp1 (Mat image, int x, int y) {
	int w = image.size().width, h = image.size().height; 
	Size size(w, h);	
	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);
	warpPerspective(image, image, matrix, size);
	Rect roi(Point2i(472,52), Point2i(800,830));
	return image;
}
Mat warp(Mat img,int x, int y) {
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


	int w = img.size().width, h = img.size().height; //	w = 1920 h = 1080*scale	//
	Size size(w, h);	//	Input image resolution as checked by image properties also	//
	cout<<w<<" "<<h<<endl;


	//	we take input as taken by Riju Ma'am, i.e top left point first and then in anti clockwise direction	//
	//	these points below for destination transformation are as given by Riju Ma'am on the Course Website	//
	float scale=(float)1920/(float)(x);
	float scale1=(float)1080/(float)(y);
	Pts_dst.push_back(Point2f((int)((float)472/scale), (int)((float)52/scale1)));
	Pts_dst.push_back(Point2f((int)((float)472/scale), (int)((float)830/scale1)));
	Pts_dst.push_back(Point2f((int)((float)800/scale), (int)((float)830/scale1)));
	Pts_dst.push_back(Point2f((int)((float)800/scale), (int)((float)52/scale1)));
	//inputPts.push_back(Point2f(996,210));
	inputPts.push_back(Point2f((int)((float)996/scale), (int)((float)210/scale1)));
	//inputPts.push_back(Point2f(415,1007));
	inputPts.push_back(Point2f((int)((float)415/scale), (int)((float)1007/scale1)));
	//inputPts.push_back(Point2f(1545,1008));
	inputPts.push_back(Point2f((int)((float)1545/scale), (int)((float)1008/scale1)));
	//inputPts.push_back(Point2f(1282,223));
	inputPts.push_back(Point2f((int)((float)1282/scale), (int)((float)223/scale1)));


	//	Take Points as Input	//
	cvtColor(img, imgGray, COLOR_BGR2GRAY); //	rgb to grayscale	//
	//imshow("Original Frame", imgGray);

	//setMouseCallback("Original Frame", getPointsFromUser, &inputPts);	// take input
	//waitKey(0);	//	wait for infinite time till user presses any key.

	//	Transform now!	//
	Mat matrix = getPerspectiveTransform(inputPts, Pts_dst);	// get homography matrix
	warpPerspective(imgGray, transformedGray, matrix, size);
	//resize(transformedGray, transformedGray, Size(), 0.5, 0.5);


	//	cropping	//
	Rect roi(Point2i((int)((float)472/scale),(int)((float)52/scale1)), Point2i((int)((float)800/scale),(int)((float)830/scale1)));	//rect structure for cropping
	croppedImg = transformedGray(roi);

	waitKey(0);
	return croppedImg;
}

Mat warpWithoutUserInput(Mat image,int x, int y){
	int w = image.size().width, h = image.size().height; //	w = 1920*scale h = 1080*scale	//
	float scale=(float)1920/float(x);
	float scale1=(float)1080/float(y);
	Size size(w, h);	//	Input image resolution as checked by image properties also	//

	// 	MODIFIED
	Mat matrix = getPerspectiveTransform(inputPts_scaled, Pts_dest_scaled);
	warpPerspective(image, image, matrix, size);
	Rect roi(Point2i((int)((float)472/scale),(int)((float)52/scale1)), Point2i((int)((float)800/scale),(int)((float)830/scale1)));	//rect structure for cropping
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

float getx1 () {return inputPts[0].x;}
float gety1 () {return inputPts[0].y;}
float getx2 () {return inputPts[1].x;}
float gety2 () {return inputPts[1].y;}
float getx3 () {return inputPts[2].x;}
float gety3 () {return inputPts[2].y;}
float getx4 () {return inputPts[3].x;}
float gety4 () {return inputPts[3].y;}
