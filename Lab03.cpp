/**
 * Lab 03 - Creating images and accessing pixels
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 * 
 * We, (named above), declare that the attached assignment is our own work in accordance with the Seneca 
 * Academic Policy.  We have not copied any part of this assignment, manually or electronically, from any 
 * other source including web sites, unless specified as references. We have not distributed our work to 
 * other students.  
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <string>
#include <sstream>

int main(int argc, char** argv) {

  std::string WINDOW_NAME = "Lab 03";
  cv::Mat bg = cv::Mat::zeros(480, 640, CV_8UC3);

  cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
  cv::imshow(WINDOW_NAME, bg);
  cv::waitKey(1);

  int key;
  bool done = false;
  


  while (!done) {

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    std::cout << "Please enter the top left x value: ";
    std::cin >> x1;
    std::cout << "Please enter the top left y value: ";
    std::cin >> y1;
    std::cout << "Please enter the bottom right x value: ";
    std::cin >> x2;
    std::cout << "Please enter the bottom right y value: ";
    std::cin >> y2;

    cv::Point point1(x1, y1), point2(x2, y2);

    if (!point1.inside(cv::Rect(cv::Point(0, 0), cv::Point(bg.size().width, bg.size().height))) ||
      !point2.inside(cv::Rect(cv::Point(0, 0), cv::Point(bg.size().width, bg.size().height))) ||
        point2.x < point1.x || point2.y < point1.y) {
      std::cout << "You have provided coordinates outside of 480 x 640." << std::endl;
      continue;
    }

    std::cout << std::endl;

    char colour;
    std::cout << "Please enter a letter that corresponds to a colour: " << std::endl;
    std::cout << "  k: black" << std::endl;
    std::cout << "  w: white" << std::endl;
    std::cout << "  r: red" << std::endl;
    std::cout << "  g: green" << std::endl;
    std::cout << "  b: blue" << std::endl;
    std::cout << "  c: cyan" << std::endl;
    std::cout << "  y: yellow" << std::endl;
    std::cout << "  m: magenta" << std::endl;
    std::cout << "  x: random" << std::endl;

    std::cout << "Choice: ";
    std::cin >> colour;

    cv::Scalar sColour;

    if (colour == 'k') sColour = cv::Scalar(0, 0, 0);
    else if (colour == 'w') sColour = cv::Scalar(255, 255, 255);
    else if (colour == 'r') sColour = cv::Scalar(0, 0, 255);
    else if (colour == 'g') sColour = cv::Scalar(0, 255, 0);
    else if (colour == 'b') sColour = cv::Scalar(255, 0, 0);
    else if (colour == 'c') sColour = cv::Scalar(255, 255, 0);
    else if (colour == 'y') sColour = cv::Scalar(0, 255, 255);
    else if (colour == 'm') sColour = cv::Scalar(255, 0, 255);
    else if (colour == 'x') sColour = cv::Scalar(rand() % 256, rand() % 256, rand() % 256);
    else sColour = cv::Scalar(rand() % 256, rand() % 256, rand() % 256);

    for (int x = 0; x < bg.cols; x++) {
      for (int y = 0; y < bg.rows; y++) {
        if (x >= point1.x && x <= point2.x &&
            y >= point1.y && y <= point2.y) {
          cv::Vec3b &colour = bg.at<cv::Vec3b>(cv::Point(x, y));
          colour[0] = sColour[0];
          colour[1] = sColour[1];
          colour[2] = sColour[2];
        }
      }
    }

    std::cout << std::endl;
    cv::imshow(WINDOW_NAME, bg);
    cv::waitKey(1);

    cv::Rect check(point1, point2);

    std::cout << "Width: " << check.width << std::endl << "Height: " << check.height << std::endl;

    CvPoint checkPoint;


    std::cout << "Specify coordinate x of a point to check it's in the rectangle: ";
    std::cin >> checkPoint.x;
    std::cout << "Specify coordinate y of a point to check it's in the rectangle: ";
    std::cin >> checkPoint.y;

    if (check.contains(checkPoint)) {
      std::cout << "The point is within the rectangle!" << std::endl << std::endl;
    }
    else {
      std::cout << "The point is not within the rectangle!" << std::endl << std::endl;
    }

    char cont;
    std::cout << "Would you like to make another rectangle? (Y/n): ";
    std::cin >> cont;

    if (cont == 'n') done = true;
    else std::cout << std::endl;
  }

  cv::imwrite("Lab03.jpg", bg);

  return 0;
}