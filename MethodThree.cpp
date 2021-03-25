#include "MethodThree.hpp"

using namespace cv;
using namespace std;

void performMethod3 (Mat& backGround, VideoCapture& cap, ofstream& file,  int queueLength,int x,int y){
   int width = x;
   int height = y;
   resize(backGround,backGround,Size(x,y));
   cap.set(CAP_PROP_FRAME_HEIGHT, height);
   cap.set(CAP_PROP_FRAME_WIDTH, width);
   performSubtask2 (backGround, cap, file, 5, x, y);
}

