/**
 * Lab 02 - Creating images and capturing video
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>

void help(char** argv) {
  std::cout << "\n"
    << "\nxample 2-10. The same object can load videos from a camera or a file"
    << "\nCall:\n"
    << argv[0] << " [path/image]\n"
    << "\nor, read from camera:\n"
    << argv[0]
    << "\nFor example:\n"
    << argv[0] << " ../tree.avi\n"
    << std::endl;
}


int main(int argc, char** argv) {

  help(argv);

  std::string WINDOW_NAME = "Lab 02";

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


    // Use std::cout to output the widthand height of the video capture object using GET member function.
    //change
    if (displayResolution == true) {
      displayResolution = false;
      width = (int) cap.get(cv::CAP_PROP_FRAME_WIDTH);
      height = (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT);
      std::cout << "Height: " << height << std::endl
        << "Width: " << width << std::endl;
    }

    key = cv::waitKey(wait);

    if (key == 13 || key == 32) break;
    else if (key == 120) {
      std::ostringstream file_increment;
      std::string filename;

      file_increment << std::setw(2) << std::setfill('0') << count++;

      width = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
      height = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
      
      filename =
        "image-" + std::to_string(width) + "x" + std::to_string(height) + "-" + 
        file_increment.str() + ".jpg";

      cv::imwrite(filename, frame);
      cv::waitKey(1000);
    }

  }

  return 0;
}