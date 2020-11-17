/**
 * Lab 05 - Histograms & Filtering
 * File: Lab05_1.cpp
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

    Mat image1 = imread("./useMeTwo.jpg");

    if (image1.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    cout << "\nPart I: Histograms" << endl;
    cout << "------------------------" << endl;

    imshow("Original Image", image1);
    waitKey(500);

    // Convert image to grayscale
    Mat greyImage1;
    cvtColor(image1, greyImage1, COLOR_BGR2GRAY);

    Mat hist;

    imshow("Grey scale", greyImage1);
    // Apply histogram equalization to grayscale image and display the results
    Mat equalizedImage1;
    equalizeHist(greyImage1, equalizedImage1);
    imshow("Equalized Image", equalizedImage1);

    waitKey();
    
}