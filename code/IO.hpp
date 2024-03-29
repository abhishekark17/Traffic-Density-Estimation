
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

using namespace cv;
using namespace std;


// vector<Point2f> inputPts;	// 4 pts taken from user to select the area of interest	//
// vector<Point2f> Pts_dst;	// destination pts.	//
// Mat imgGray; //backGroundground image displayed which will be used for selecting the four points//
void initializeInputPts (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void initializeDestPts ();
void initializeInputPtsScaled (int x, int y);
void initializeDestPtsScaled (int x, int y);


void getPointsFromUser(int event, int x, int y, int flags, void* userData);
Mat warp(Mat img);
Mat warp(Mat img,int x,int y);
Mat warpWithoutUserInput(Mat image);
Mat warpWithoutUserInput(Mat image,int x,int y);
Mat warpSpecial (Mat img);
void performOutput (int whitePixels1, int whitePixels2, int totalPixels, int frameNumber, ofstream& file);
void performOutputM1(int whitePixels1,int whitePixels2,int totalPixels,int frameNumber,ofstream& file,int x);

float getx1 ();
float gety1 ();
float getx2 ();
float gety2 ();
float getx3 ();
float gety3 ();
float getx4 ();
float gety4 ();

