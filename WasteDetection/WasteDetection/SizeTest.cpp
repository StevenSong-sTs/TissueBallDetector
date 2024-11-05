#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

//int main() {
//
//    string path = "Resources/img1.jpg";
//    Mat img = imread(path);
//    Mat imgResize;
//
//   
//    resize(img, imgResize, Size(), 0.2,0.2 );
//    
//    imshow("Image", imgResize);
//    waitKey(0);
//    return 0;
//
//}


/////////////////  Webcam  //////////////////////

int main() {

	VideoCapture cap(0);
	Mat img;

	while (1) {

		cap.read(img);

		imshow("image", img);
		waitKey(1);
	}

	return 0;
}