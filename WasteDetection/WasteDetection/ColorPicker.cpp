#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  ColorPicker //////////////////////

Mat imgResize, imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

int main() {

    string path = "Resources/img1.jpg";
    Mat img = imread(path);
   
    resize(img, imgResize, Size(), 0.2, 0.2);
    cvtColor(imgResize, imgHSV, COLOR_BGR2HSV);

    namedWindow("ColorPicker", (640, 200));
    createTrackbar("Hue Min", "ColorPicker", &hmin, 179);
    createTrackbar("Hue Max", "ColorPicker", &hmax, 179);
    createTrackbar("Sat Min", "ColorPicker", &smin, 255);
    createTrackbar("Sat Max", "ColorPicker", &smax, 255);
    createTrackbar("Val Min", "ColorPicker", &vmin, 255);
    createTrackbar("Val Max", "ColorPicker", &vmax, 255);

   
    while (true) {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);
        cout << lower << upper << endl;

        imshow("Image", imgResize);
        imshow("ImageHSV", imgHSV);
        imshow("ImageMask", mask);
        waitKey(1);
    }
    return 0;
}