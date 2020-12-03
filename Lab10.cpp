/**
 * Lab 10 - Motion Detection and Segmentation
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 * File: Lab10_1.cpp
 * 
 * We, (named above), declare that the attached assignment is our own work in accordance with the Seneca
 * Academic Policy. We have not copied any part of this assignment, manually or electronically, from any
 * other source including web sites, unless specified as references. We have not distributed our work to
 * other students.
 * 
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {

    std::cout << "Part I: Motion Detection" << std::endl;

    std::string WINDOW_NAME = "Lab 10";

    cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;

    if (argc == 1) {
        cap.open(0); // open the first camera
    }
    else {
        cap.open(argv[1]);
    }

    if (!cap.isOpened()) { // check if we succeeded
        std::cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::Mat gray;

    int count = 1;
    int key = 0;
    int wait = 33;
    bool displayResolution = true;
    int width;
    int height;

    while (true) {

        cap >> frame;

        if (frame.empty()) break;

        cv::imshow(WINDOW_NAME, frame);
        key = cv::waitKey(wait);

        bool firstCap = true;

        // Esc or spacebar to exit, enter to capture image
        if (key == 27 || key == 32) break;
        else if (key == 13) {

            cvtColor(frame, gray, CV_BGR2GRAY);

            if (firstCap) {
                cv::imwrite("back.jpg", gray);
                cv::waitKey(1000);

                firstCap = false;
            }
            else {
                cv::imwrite("diff.jpg", gray);
                cv::waitKey(1000);
            }

            



            //Apply the following changes :

            //a.Convert the captured frames to grayscale.
            //b.Save the first frame(converted to grayscale) as background image.
            //c.Change code to display the difference images, instead of captured frames.
            //d.Threshold the difference image using a threshold of 128.
            //e.Count the number of pixels changed by at least 128 gray levels, by finding the sum of the threshold image in part d.
            //f.If the count is larger than 1 % of the frame size,
                //i.Make a beep sound
                //ii.Output the time the activity was detected
                //iii.Save the current color frame in a file(with a counter or time stamp)
                //iv.Update the background image
                //v.Wait for 2 seconds before returning to capturing loop.

            //g.Exit the program by entering esc or space. DONE
            //h.Adjust the motion sensitivity(1 % of the frame size) to your desired sensitivity.

        }

    }

    return 0;

}