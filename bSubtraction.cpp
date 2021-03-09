#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>


using namespace cv;
using namespace std;

vector<Point2f> inputPts;	// 4 pts taken from user to select the area of interest	//
vector<Point2f> Pts_dst;	// destination pts.	//
Mat imgGray; //Background image displayed which will be used for selecting the four points//

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
//This part was used to get the background images with no vehicles.(should be used to get background image at appropriate time)
/*
void getBackground(String path){
	VideoCapture cap(path);
	int currentFrame=0;
	String filepath;
	while(true) {
		Mat frame;
		cap>>frame;
		filepath="images/a"+to_string(currentFrame);
		filepath=filepath+".jpg";
		if (currentFrame % 15 ==0){
			imwrite(filepath,frame);
		}
		currentFrame+=1;
	}
}
*/

/*
//This function finds the contours and give the bounding box around the object
void getContours(Mat image,Mat imgOriginal){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(image,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for(int i=0;i<contours.size();i++){
		int area = contourArea(contours[i]);
		if(area>1000 && area<5000){
			float peri = arcLength(contours[i],true);
			approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
			//drawContours(imgOriginal,conPoly,-1,Scalar(255,0,255),2);
			boundRect[i]=boundingRect(conPoly[i]);
			rectangle(imgOriginal,boundRect[i].tl(),boundRect[i].br(),Scalar(255,0,255),2);

		}
	}

}
*/

/*
//Object detection and application of contour function
void edgeDetector(Mat image,Mat imgOriginal){
	Mat imgBlur,imgCanny,imgDil,imgErode;
	//preprocessing
	GaussianBlur(image,imgBlur,Size(3,3),3,0);
	Canny(imgBlur,imgCanny,25,75);
	Mat kernel=getStructuringElement(MORPH_RECT,Size(3,3));
	dilate(imgCanny,imgDil,kernel);

	//contour detection
	getContours(imgDil,imgOriginal);

}
*/



int main(int argc, char* argv[])
{
    String videopath="video/trafficvideo.mp4";
   
    //getBackground(videopath);
    String imagepath="images/emptyBackground.jpg";
    Mat back;
	back = imread(imagepath);
    back = warp(back);

    VideoCapture cap(videopath);
    //Ptr<BackgroundSubtractor> bsub;
    //bsub=createBackgroundSubtractorMOG2();
    Mat frame,fmask,frameGray;
    //int countOnLine1,countOnLine2;
    //Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	ofstream file("data.csv");
	file<<"Frame,QueueDensity\n";
	int frameNumber=0;
    while(true){
    	
    	cap>>frame;

		frameNumber+=1;
		//warping individual frames one by one
		frame=warpWithoutUserInput(frame);
		cvtColor(frame,frameGray,COLOR_RGB2GRAY,0);

    	
    	//bsub->apply(frameGray,fmask);
    	//morphologyEx(fmask, fmask,MORPH_ELLIPSE, kernel);

    	absdiff(frameGray,back,fmask);
    	//imshow("normal",frame);
    	threshold( fmask, fmask, 30,255,THRESH_BINARY);
    	//edgeDetector(fmask,fmask);
		int totalPixels = fmask.rows*fmask.cols;
		int whitePixels = countNonZero(fmask);
		float density = (float)whitePixels/(float)totalPixels;
		file<<frameNumber<<","<<density<<"\n";
    	// line(fmask, Point(0, 10), Point(fmask.cols, 10), Scalar(255,255,255), 3);
    	// line(fmask, Point(0, fmask.rows-10), Point(fmask.cols, fmask.rows-10), Scalar(255,255,255), 3);
		imshow("final",fmask);
		if(waitKey(1)==27) {
    		break;
    	}

    }
	file.close();
    destroyAllWindows();
    return 0;
}
