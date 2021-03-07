#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

//This part was used to get the background images with no vehicles.
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

int main(int argc, char* argv[])
{
    String videopath="video/trafficvideo.mp4";
   
    //getBackground(videopath);
    String imagepath="images/emptyBackground.jpg";
    Mat back;
    back=imread(imagepath,IMREAD_GRAYSCALE);
    VideoCapture cap(videopath);
    Ptr<BackgroundSubtractor> bsub;
    bsub=createBackgroundSubtractorMOG2();
    Mat frame,fmask;
    //Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    while(true){
    	
    	cap>>frame;
    	cvtColor(frame,frame,COLOR_RGBA2GRAY,0);
    	//bsub->apply(frame,fmask);
    	//morphologyEx(fmask, fmask,MORPH_ELLIPSE, kernel);
    	absdiff(frame,back,fmask);
    	
    	
    	//imshow("normal",frame);
    	imshow("Amsked",fmask);
    	if(waitKey(1)==27) {
    		destroyAllWindows();
    		break;
    	}

    }
    destroyAllWindows();


    
    return 0;
}