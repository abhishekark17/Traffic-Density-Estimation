
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/video/tracking.hpp>


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

Mat filterImage (Mat img_bw) {
    //img_bw = img_bw > 5;

    // Define the structuring elements
    Mat se1 = getStructuringElement(MORPH_ELLIPSE, Size(4, 4));
    Mat se2 = getStructuringElement(MORPH_ELLIPSE, Size(4, 4));

    // Perform closing then opening
    Mat mask;
    morphologyEx(img_bw, mask, MORPH_CLOSE, se1);
    morphologyEx(mask, mask, MORPH_OPEN, se2);

    // Filter the output
    Mat out = mask.clone();
    out.setTo(Scalar(0), mask == 0);

	return out;
}

Mat performBackgroundSubtraction (Mat& inputFrame, Mat& backGround) {
	Mat queueDensityImg;
	absdiff(inputFrame , backGround , queueDensityImg);
	threshold( queueDensityImg, queueDensityImg, 25, 255, THRESH_BINARY);
	return queueDensityImg;
}

Mat performOpticalFlow (Mat& previous, Mat& next ) {
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5)); 

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
	morphologyEx(opticalFlowOutput, opticalFlowOutput,MORPH_ELLIPSE, kernel);
	threshold( opticalFlowOutput, opticalFlowOutput, 12 ,255,THRESH_BINARY);
	return opticalFlowOutput;
}

void performOutput (int whitePixels1, int whitePixels2, int totalPixels, int frameNumber, ofstream& file) {
	float queueDensity = (float) whitePixels1 / (float) totalPixels;
	float dynamicDensity = (float) whitePixels2 / (float) totalPixels;

	file << (float) frameNumber / (float) (15.0) << "," << queueDensity << "," << dynamicDensity << endl;
	cout << frameNumber << "," << dynamicDensity << "," << dynamicDensity << "\n";

	return;
}

int main(int argc, char* argv[])
{	
	//	Initialize I/O	//
	String imagepath="images/emptyBackground.jpg";
	string videopath="video/trafficvideo.mp4";
	ofstream file("data.csv");	
	if (argc==1) cout<<"Video file should be given as argument"<<endl;
	else{
		string videoFileName=argv[1];
		videopath = "video/"+videoFileName;
	}
    VideoCapture cap(videopath);

	if (!cap.isOpened()) {
		cout << "Error: video file is empty" << endl;
		return -1;
	}
	

    //	backGround :: Fixed background for background subtraction for vehicular density	//
    Mat backGround = imread(imagepath);
    backGround = warp(backGround);
	int totalPixels = backGround.rows * backGround.cols;

	// previous :: First frame of the video to begin optical flow. Later on will be used as previous frame in while loop for optical flow	//
	Mat previous; cap >> previous;
	cvtColor(previous , previous, COLOR_BGR2GRAY);
	previous = warpWithoutUserInput(previous);


	file<<"Frame,QueueDensity,DynamicDensity\n";
	cout<<"Frame,QueueDensity,DynamicDensity\n";
	int frameNumber=0;

    while(true){	
		Mat inputNextFrame; 
		cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;cap >> inputNextFrame;
		if (inputNextFrame.empty()) break;
		frameNumber += 5;	//	taking every 5th frame - Ma'am said we can take every 3rd or 5th	//

		cvtColor(inputNextFrame, inputNextFrame, COLOR_BGR2GRAY);
		inputNextFrame = warpWithoutUserInput(inputNextFrame);
		imshow("Original Video" , inputNextFrame);
		

		Mat queueDensityImg = performBackgroundSubtraction(inputNextFrame, backGround);
		Mat dynamicDensityImg = performOpticalFlow(previous, inputNextFrame);
		imshow("Background Subtraction Output" , queueDensityImg);
		imshow("Optical Flow Output" , dynamicDensityImg);

		int whitePixels1 = countNonZero(queueDensityImg);
		int whitePixels2= countNonZero(dynamicDensityImg);

		performOutput(whitePixels1, whitePixels2, totalPixels, frameNumber, file);
		
		int keyboard = waitKey(1);
        if (keyboard == 'q' || keyboard == 27) break;
		previous = inputNextFrame;
    	
    }
	file.close();
    destroyAllWindows();
    return 0;
}