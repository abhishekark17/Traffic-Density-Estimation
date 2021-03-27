#include "MethodThree.hpp"

using namespace cv;
using namespace std;

void performMethod3 (Mat& backGround, VideoCapture& cap, ofstream& file,  int queueLength,int x,int y){
   int64 width = x;
   int64 height = y;
   Size size(width,height);
   resize(backGround,backGround,size);
   cap.set(CAP_PROP_FRAME_HEIGHT, height);
   cap.set(CAP_PROP_FRAME_WIDTH, width);
   performSubtask2 (backGround, cap, file, 5, x, y);
}

