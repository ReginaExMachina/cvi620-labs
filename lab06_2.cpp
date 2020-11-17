/**
 * Lab 06 - Part 2 - Geometric transformations
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 *
 * We, (named above), declare that the attached assignment is our own work in accordance with the Seneca
 * Academic Policy.  We have not copied any part of this assignment, manually or electronically, from any
 * other source including web sites, unless specified as references. We have not distributed our work to
 * other students.
 */

#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;


void rotate(cv::Mat& src) {
	double angle;
	cout << "please insert the rotation angle: ";
	cin >> angle;
	cv::Mat rotationMatrix = cv::getRotationMatrix2D(cv::Point2f(src.cols / 2.0, src.rows / 2.0), angle, 1);
	cout << endl << rotationMatrix << endl << endl;
	cv::warpAffine(src, src, rotationMatrix, src.size());
}


void resize(cv::Mat& src) {

	double fx, fy;

	cout << "Resizing factor for x-axis: ";
	cin >> fx;

	cout << "Resizing factor for y-axis: ";
	cin >> fy;

	cv::resize(src, src, cv::Size(fx, fy), fx, fy);
}

void applyPerspectiveTransformation(cv::Mat& src) {
	cv::Mat homographyMatrix = (cv::Mat_<double>(3, 3) << .4, -.4, 190, .15, .4, 100, 0, 0, 1);
	cv::warpPerspective(src, src, homographyMatrix, src.size());
}


int main(int argc, char** argv) {

	std::string windowName = "Original Image";

	cv::Mat src = cv::imread("./furiouscamera.jpg");

	cv::imshow(windowName, src);

	cv::waitKey(500);
	int count = 1;


	while (true) {
		int option;
		cout << "Manipulate Image: \n 1: Rotate \n 2: Resize \n 3: Apply perspective transformation \n 0: Exit \n Input: ";
		cin >> option;

		if (option == 0) {
			break;
		}
		else {
			switch (option)
			{
			case 1: {
				rotate(src);
				windowName = "Rotation Applied";
				break;
			}
			case 2: {
				resize(src);
				windowName = "Resize Applied";
				break;
			}
			case 3: {
				applyPerspectiveTransformation(src);
				windowName = "Perspective Transformation Applied";
				break;
			}
			default:
				break;
			}
		}
		cv::imwrite("image-" + std::to_string(count++) + ".png", src);
		cv::imshow(windowName, src);
		cv::waitKey();
	}
}