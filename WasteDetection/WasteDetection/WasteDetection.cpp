#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

Mat imgHSV, mask;

void getContour(Mat mask, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> contourPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		int area;
		area = contourArea(contours[i]);
		//cout << area << endl;

		if (area > 800 && area < 2000) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);
			//drawContours(img, contours, i, Scalar(255, 0, 0), 2);
			//cout << contourPoly[i].size() << endl;

			if (contourPoly[i].size() > 7 && contourPoly[i].size() < 15) {
				boundRect[i] = boundingRect(contourPoly[i]);
				rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
				putText(img, "waste", {boundRect[i].x, boundRect[i].y-5 }, FONT_HERSHEY_DUPLEX, 0.75, Scalar(255, 255, 255), 2);
			}
		}
	}
}



void detect(Mat img) {

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	Scalar lower(85, 0, 180);
	Scalar upper(132, 62, 255);
	inRange(imgHSV, lower, upper, mask);

	getContour(mask,img);
}

int main() {

	VideoCapture cap(0);
	Mat img;

	while (1) {

		cap.read(img);
		detect(img);

		imshow("WasteDetection", img);
		imshow("imageMask", mask);
		waitKey(1);
	}

	return 0;
}