#include <iostream>
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
Mat greyBG;
vector<Point2f> ip;	

void getPointsFromUser(int event, int x, int y, int flags, void* userData) {
	if (event == EVENT_LBUTTONDOWN) {
		imshow("Original Frame", greyBG);
		if (ip.size() < 4) ip.push_back(Point2f(x, y));
	}
}



int main () {
    ofstream f;
    f.open("ip.txt");

    String imagepath="../images/emptyBackground.jpg";
    Mat backGround = imread(imagepath);

    cvtColor(backGround, backGround, COLOR_BGR2GRAY); //	rgb to grayscale	//
    greyBG = backGround;

    ip.clear();
    imshow("Original Frame", greyBG);
	setMouseCallback("Original Frame", getPointsFromUser, &ip);	
	waitKey(0);
    destroyWindow("Original Frame");

    f << (int) ip[0].x << endl;
    f << (int) ip[0].y << endl;
    f << (int) ip[1].x << endl;
    f << (int) ip[1].y << endl;
    f << (int) ip[2].x << endl;
    f << (int) ip[2].y << endl;
    f << (int) ip[3].x << endl;
    f << (int) ip[3].y << endl;

    f.close();
    cout << "Points read and saved in ip.txt\n";
    return 0;
}