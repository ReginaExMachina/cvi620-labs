/**
 * Lab 08 - Evaluation Measures
 * File: Lab08.cpp
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 *
 *  We, (named above), declare that the attached assignment is our own work in accordance with the Seneca
 * Academic Policy. We have not copied any part of this assignment, manually or electronically, from any
 * other source including web sites, unless specified as references. We have not distributed our work to
 * other students.
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>

/**
* Part I Functions
*
*/
    
        /**
        * Calculates precision and recall for a binary classfier  
        * 
        * @pred pointer to classifier predictions
        * @gt pointer to ground truth classes
        * @len length of pred and gt arrays 
        * 
        * @P pointer to return precision
        * @R pointer to return recall
        * 
        * Returns 1 if successful, 0 otherwise
        */
        int calcPR(bool *pred, bool *gt, int len, double *P, double *R) {

        }

        /**
        * Calculates F(?) 
        * 
        * Returns the F1 measure
        */
        double calcFb(double P, double R, double beta) {

        }

        // /**
        //  * Reads csv files as classifier predictions and ground truths
        //  * 
        //  */

/**
* Part II Functions
*
*/

        // /**
        //  * Converts the response of a continuous classifier to a Boolean given a threshold
        //  * 
        //  * @A pointer to continous response
        //  * @B pointer to Boolean response
        //  * @len length of arrays
        //  * @thresh threshold
        //  * 
        //  * Converts continous response to true or false
        //  */
        // void thresh_v(double *A, bool *B, int len, double thresh) {

        // }

        // /**
        //  * Reads continous response in csv files
        //  */

/**
* Part III Functions
*
*/

        // // Converts image to a Boolean array
        // void thresh_img(Mat img, bool *B, double thresh) {

        // }
int main(int argc, char** argv) {

    char option;
    std::cout << "Choose an option A/B/C/D: ";
    std::cin >> option;

    if (option == 'A') {
        
        std::cout << "\nPart I: Evaluating a binary classifier" << std::endl;

        // /**
        //  * Main Program:
        //  * Write code to calculate precision, recall and F1
        //  */ 

    }
    else if (option == 'B') {
        std::cout << "\nPart II: Evaluating a binary classifier with a continous response" << std::endl;

        // /** 
        //  * Main Program:
        //  * Using the above functions, write code to calculate precision, recall and F1
        //  * for the above classifier and for threshold values:
        //  * 
        //  * 0.1, 0.2, 0.3 ... 0.8, 0.9
        //  * 
        // */ 


        // // Write the evaluation measures to PR.csv

    }
    else if (option == 'C') {

        std::cout << "\nPart III: Evaluating image-based classifiers" << std::endl;

        // // 1. Open image as grayscale
        // cv::Mat src = cv::imread("./bitmap_A1.png", 0);
    
        // if (src.empty()) {
        //     std::cout << "Error: No image found." << std::endl;
        //     return -1;
        // }

        // cv2.imshow("Greyscale", src);
        // cv2.waitKey(200);

        // // 2. Open image as ground truth --- What does this mean?

        // // 4. Using the above functions, write code to calculate precison, recall and F1 measure for the above classfier

    }
    else if (option == 'D') {
        std::cout << "\nPart IV: Evaluating image-based classifiers wit continous repsonses" << std::endl;

        // // 1. Open image as grayscale
        //     cv::Mat src2 = cv::imread("./bitmap_A2.png", 0);
    
        // if (src2.empty()) {
        //     std::cout << "Error: No image found." << std::endl;
        //     return -1;
        // }

        // cv2.imshow("Greyscale", src2);
        // cv2.waitKey(200);

        // // 2. Calculate precision, recall and F1 with the following threshold values:
        // // 25, 50, ..., 225, 250

        // // a. Write the evaluation measures to PR_img.csv

    }
    else {
        std::cout << "\nInvalid option" << std::endl;
    }

}
