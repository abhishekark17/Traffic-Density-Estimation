#include "mymain.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{	
	//	Initialize I/O	//
	String imagepath="images/emptyBackground.jpg";
	string videopath="video/trafficvideo.mp4";

	//ofstream file("data.csv");	
	//ofstream fileM1 ("dataM1.csv");
	ofstream fileM2 ("dataM2.csv");
	//ofstream fileM3 ("dataM3.csv");
	//ofstream fileM4 ("dataM4.csv");
	//ofstream fileM5 ("dataM5.csv");

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

	//	This was for Assignment Subtask-2	//
	//performSubtask2(backGround, cap, file, 5);


	//performMethod1 (backGround,cap,fileM1,4,10);
	performMethod2 (backGround, cap, fileM2, 4);
	//performMethod3 (backGround, cap, fileM3, 5,1080,720);

	//file.close();
	//fileM1.close();
	fileM2.close();
	//fileM3.close();
	//fileM4.close();
	//fileM5.close();
    return 0;
}