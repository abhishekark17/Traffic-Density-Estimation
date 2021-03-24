#include "MethodTwo.hpp"

using namespace cv;
using namespace std;

// Sparse Optical Flow: https://docs.opencv.org/3.4/d4/dee/tutorial_optical_flow.html#:~:text=Dense%20Optical%20Flow%20in%20OpenCV&text=Lucas%2DKanade%20method%20computes%20optical,the%20points%20in%20the%20frame.

void performMethod2 (Mat& backGround, VideoCapture& cap, ofstream& file,  int queueLength) {
    
    backGround = warp(backGround);
	int totalPixels = backGround.rows * backGround.cols;

    // Create some random colors
    vector<Scalar> colors;
    RNG rng;
    for(int i = 0; i < 100; i++) {
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(Scalar(r,g,b));
    }


	queue<Mat> myQueue;
    
	for (int i = 0; i < queueLength; i++) {
		Mat temp;
        cap >> temp;

		cvtColor(temp,temp,COLOR_BGR2GRAY);
		temp = warpWithoutUserInput(temp);
		myQueue.push(temp);
	}
    // Take first frame and find corners in it  //
    Mat previous = myQueue.front();
	myQueue.pop();

    cout << previous.type() << " this is the type\n";
    vector<Point2f> p0, p1;
    goodFeaturesToTrack(previous, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);

    
    // Create a mask image for drawing purposes
    Mat mask = Mat::zeros(previous.size(), previous.type());



	file<<"Frame,QueueDensity,DynamicDensity\n";
	cout<<"Frame,QueueDensity,DynamicDensity\n";
	int frameNumber = queueLength;   
    
    while (true) {
        Mat inputNextFrame; 
        cap >> inputNextFrame;

        if (inputNextFrame.empty()) break;
        frameNumber++;

        cvtColor(inputNextFrame, inputNextFrame, COLOR_BGR2GRAY);
		inputNextFrame = warpWithoutUserInput(inputNextFrame);
		myQueue.push(inputNextFrame);

		imshow("Original Video" , inputNextFrame);


        // copy pasted code.
        // calculate sparse optical flow
        vector<uchar> status;
        vector<float> err;
        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(previous, inputNextFrame, p0, p1, status, err, Size(15,15), 2, criteria);


        Mat queueDensityImg = performBackgroundSubtraction(inputNextFrame, backGround);
		//Mat dynamicDensityImg = performOpticalFlow(previous, inputNextFrame);
		imshow("Background Subtraction Output" , queueDensityImg);
		//imshow("Optical Flow Output" , dynamicDensityImg);

		int whitePixels1 = countNonZero(queueDensityImg);
		//int whitePixels2= countNonZero(dynamicDensityImg);

		//performOutput(whitePixels1, whitePixels2, totalPixels, frameNumber, file);
		//for (int i = 1; i < x; i++) performOutput(whitePixels1,whitePixels2,totalPixels,frameNumber + i,file);
        //performOutputM1(whitePixels1,whitePixels2,totalPixels,frameNumber,file, x);

        Mat forOutput = Mat::zeros(previous.size(), previous.type()) ;
        for (auto x: p1) forOutput.at<uchar>(x) = 255;

        imshow ("check it", forOutput);


        vector<Point2f> good_new;
        for(uint i = 0; i < p0.size(); i++) {
            // Select good points
            if(status[i] == 1) {
                good_new.push_back(p1[i]);
                // draw the tracks
                line(mask,p1[i], p0[i], colors[i], 2);
                circle(inputNextFrame, p1[i], 5, colors[i], -1);
            }
        }

        Mat img;
        add (inputNextFrame, mask, img);
        imshow ("Sparse Optical Flow Output", img);


        int keyboard = waitKey(1);
        if (keyboard == 'q' || keyboard == 27) break;

		previous = myQueue.front();
		myQueue.pop();

        p0 = good_new;


    }

    destroyAllWindows();
    return;
}
