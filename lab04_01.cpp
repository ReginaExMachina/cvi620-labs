///**
// * Lab 03 - Creating images and accessing pixels
// *
// * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
// *
// * We, (named above), declare that the attached assignment is our own work in accordance with the Seneca
// * Academic Policy.  We have not copied any part of this assignment, manually or electronically, from any
// * other source including web sites, unless specified as references. We have not distributed our work to
// * other students.
// */
//
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//    Mat imageOne = imread("./useMeOne.jpg");
//    Mat imageTwo = imread("./useMeTwo.jpg");
//
//    if (imageOne.empty())
//    {
//        cout << "Could not open or find the image!\n" << endl;
//        cout << "Usage: " << argv[0] << " <Input image>" << endl;
//        return -1;
//    }
//
//
//
//    Mat increasedBrightness = Mat::zeros(imageOne.size(), imageOne.type());
//    Mat increasedContrast = Mat::zeros(imageOne.size(), imageOne.type());
//    const double alpha = 2; 
//    const Scalar beta = Scalar(50, 50, 50);
//
//
//    char option;
//    std::cout << "Choose an option A/B: ";
//    std::cin >> option;
//
//
//
//    if (option == 'A') {
//        cout << "\nPart I: Image Arithmetic   " << endl;
//        cout << "------------------------" << endl;
//
//        increasedBrightness = Mat(imageTwo) + beta;
//        increasedContrast = Mat(imageTwo) * alpha;
//
//        imshow("Original Image", imageTwo);
//        waitKey(500);
//
//        imshow("Increased Brightness", increasedBrightness);
//        waitKey(500);
//
//        imshow("Increased Contrast", increasedContrast);
//
//        cout << "Original Image: " << (int)imageTwo.at<Vec3b>(100, 100)[0] << std::endl;
//        cout << "Increased Brightness: " << (int)increasedBrightness.at<Vec3b>(100, 100)[0] << std::endl;
//        cout << "Increased Contrast: " << (int)increasedContrast.at<Vec3b>(100, 100)[0] << std::endl;
//
//        waitKey();
//    }
//    else if (option == 'B') {
//
//        double alphaB;
//
//        imshow("Image One", imageOne);
//        imshow("Image Two", imageTwo);
//
//
//        waitKey(1000);
//
//        cout << "Enter alpha (0-1): " << std::endl;
//        cin >> alphaB;
//        waitKey(1000);
//
//        Mat blend = (1 - alphaB) * imageOne + alphaB * imageTwo;
//        waitKey(1000);
//
//        imshow("Linear Blend", blend);
//
//
//        vector<Mat> bgr_planes;
//
//        split(blend, bgr_planes);
//        
//        int histSize = 8;
//        float range[] = { 0, 256 }; //the upper boundary is exclusive
//        const float* histRange = { range };
//        bool uniform = true, accumulate = false;
//        Mat b_hist;
//       
//        calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
//
//        cout << endl <<b_hist;
//
//        waitKey();
//    }
//
//    
//
//    return 0;
//}