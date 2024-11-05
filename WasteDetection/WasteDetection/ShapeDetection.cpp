#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

Mat imgResize, imgGray, imgBlur, imgCanny, imgDil, imgErode;

void drawContours(Mat imgDil, Mat img) {

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> contourPoly(contours.size());

    for (int i = 0; i < contours.size(); i++) {
        int area;
        area = contourArea(contours[i]);
        cout << area << endl;

        if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);
            drawContours(img, contourPoly, i, Scalar(255, 0, 255), 2);
            cout << contourPoly[i].size() << endl;
        }
    }
}


int main() {

    string path = "Resources/Shape.png";
    Mat img = imread(path); 

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDil, kernel);

    drawContours(imgDil, img);

    imshow("Image", img);
    waitKey(0);
    
    return 0;

}