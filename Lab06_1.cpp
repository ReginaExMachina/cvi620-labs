/**
 * Lab 06 - Morphology & Geometric Transformations
 * File: Lab06_1.cpp
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 *
 * We, (named above), declare that the attached assignment is our own work in accordance with the Seneca
 * Academic Policy.  We have not copied any part of this assignment, manually or electronically, from any
 * other source including web sites, unless specified as references. We have not distributed our work to
 * other students.
 */

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
        Mat image1 = imread("./furiouscamera.jpg");

    if (image1.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    cout << "\nPart I: Morphology" << endl;
    cout << "------------------------" << endl;

    // Convert image to greyscale
    imshow("Original Image", image1);
    waitKey(500);

    // a. Convert image to grayscale
    Mat greyImage1;
    cvtColor(image1, greyImage1, COLOR_BGR2GRAY);

    imshow("Greyscale", greyImage1);
    imwrite("greyImage1.png", greyImage1);
    waitKey(500);
    
    // b. Convert grayscale to binary (128 as threshold)
    Mat binImage1;
    cv::threshold(greyImage1, binImage1, 128, 255, THRESH_BINARY);

    imshow("Binary Image", binImage1);
    imwrite("binImage1.png", binImage1);
    waitKey(500);
 
    // c. Apply morphological opening to binary image using 3x3 square kernel
    cv::Mat kernel = 255 * cv::Mat::ones(3, 3, CV_8UC1);
    Mat openingImage1;
    morphologyEx(binImage1, openingImage1, MORPH_OPEN, kernel);

    imshow("Opening", openingImage1);
    imwrite("openingImage1.png", openingImage1);
    waitKey(500);


    // d. Apply morphological closing to binary image using a 3x3 square kernel
    Mat closingImage1;
    morphologyEx(binImage1, closingImage1, MORPH_CLOSE, kernel);

    imshow("Closing", closingImage1);
    imwrite("closingImage1.png", closingImage1);
    waitKey(500);

    // e. Repeat last two steps usig a 7x7 kernel
    cv::Mat newKernel = 255 * cv::Mat::ones(7, 7, CV_8UC1);
    Mat openingImage2;
    morphologyEx(binImage1, openingImage2, MORPH_OPEN, newKernel);

    imshow("Opening", openingImage2);
    imwrite("openingImage2.png", openingImage2);
    waitKey(500);

    Mat closingImage2;
    morphologyEx(binImage1, closingImage2, MORPH_CLOSE, newKernel);

    imshow("Closing", closingImage2);
    imwrite("closingImage2.png", closingImage2);
    waitKey(500);
}