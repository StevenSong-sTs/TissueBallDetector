#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Webcam  //////////////////////

Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

int main() {

	VideoCapture cap(0);
	Mat img;

	namedWindow("ColorPicker", (640, 200));
	createTrackbar("Hue Min", "ColorPicker", &hmin, 179);
	createTrackbar("Hue Max", "ColorPicker", &hmax, 179);
	createTrackbar("Sat Min", "ColorPicker", &smin, 255);
	createTrackbar("Sat Max", "ColorPicker", &smax, 255);
	createTrackbar("Val Min", "ColorPicker", &vmin, 255);
	createTrackbar("Val Max", "ColorPicker", &vmax, 255);

	while (1) {

		cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(85, 0, 180);
		Scalar upper(132, 62, 255);
		inRange(imgHSV, lower, upper, mask);
		cout << lower << upper << endl;

		imshow("image", imgHSV);
		imshow("imageMask", mask);
		waitKey(1);
	}

	return 0;
}