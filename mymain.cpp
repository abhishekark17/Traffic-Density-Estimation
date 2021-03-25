#include "mymain.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{	
	//	Initialize I/O	//
	String imagepath="images/emptyBackground.jpg";
	string videopath="video/trafficvideo.mp4";
	int method = 0;
	ofstream file;
	bool closeFile = false;

	if (argc==1 || argc == 2) {
		cerr << "Video file and Method should be given as argument" << endl;
		return -1;
	}
	else{
		string videoFileName=argv[1];
		videopath = "video/"+videoFileName;
		method = stoi(argv[2]);
		if (method >5 || method < 0) {
			cerr << "Method argument should be between 0 and 5 (both included)" << endl;
			return -1;
		}
	}

	if (method < 4) closeFile = true;
	// ofstream not needed here for methods 4-5 because they are generated by threads during their respective execution.
	switch (method) {
		case 0: {
			ofstream file( "data.csv");
			break;
		}
		case 1: {
			ofstream file ("dataM1.csv");
			break;
		}
		case 2: {
			ofstream file ("dataM2.csv");
			break;
		}
		case 3: {
			ofstream file ("dataM3.csv");
			break;
		}
	}

    VideoCapture cap(videopath);
	if (!cap.isOpened()) {
		cout << "Error: video file is empty" << endl;
		return -1;
	}
	
    //	backGround :: Fixed background for background subtraction for vehicular density	//
    Mat backGround = imread(imagepath);
	

	auto startTime = chrono::high_resolution_clock::now();
	///////////////////////////////////////////////////////////	 WORKSPACE	/////////////////////////////////////////////////////////////////////

	switch (method) {
		case 0: {
			//	This was for Assignment Subtask-2	//
			performSubtask2(backGround, cap, file, 5);
			break;
		}
		case 1: {
			performMethod1 (backGround,cap,file,4,10);
			break;
		}
		case 2: {
			performMethod2 (backGround, cap, file, 4);
			break;
		}
		case 3: {
			performMethod3 (backGround, cap, file, 5,1080,720);
			break;
		}
		case 4: {
			performMethod4(videopath,backGround,5,3);
			break;
		}
		case 5: {
			// Please warp background here itself for method 5
			backGround = warp(backGround);
			performMethod5(videopath,backGround,5,5);
			break;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	auto stopTime = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds> (stopTime - startTime);

	cout << endl << endl ;
	cout << "TOTAL EXECUTION TIME (Method-" + to_string(method) +") :: " << duration.count() << " SECONDS" << endl << endl;

	if (closeFile) file.close();
    return 0;
}