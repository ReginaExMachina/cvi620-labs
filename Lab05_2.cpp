/**
 * Lab 05 - Part 2 - Histograms and Filtering
 *
 * Authors: Jade Clarke, Rachel Day, Musaddiqur Rahman
 *
 * We, (named above), declare that the attached assignment is our own work in accordance with the Seneca
 * Academic Policy.  We have not copied any part of this assignment, manually or electronically, from any
 * other source including web sites, unless specified as references. We have not distributed our work to
 * other students.
 */

#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  std::string WINDOW_NAME = "Lab 02";

  cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    return -1;
  }

  cv::Mat img = cv::imread(argv[1]);

  if (img.empty()) {
    std::cout << "Could not open or find the images!" << std::endl;
    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    return -1;
  }

  std::cout << "\nPart II: Filtering" << std::endl;
  std::cout << "------------------------" << std::endl;

  cv::imshow(WINDOW_NAME, img);
  cv::waitKey(1);

  double probability = 0.0;
  do {
    std::cout << "Please enter a number for probability >= 0.0 AND <= 1.0: ";
    std::cin >> probability;
  } while (probability < 0.0 || probability > 1.0);

  std::cout << "Adding noise to the image..." << std::endl;

  cv::RNG rng;
  cv::Mat noise(img.rows, img.cols, CV_32FC1);
  cv::Mat noisy_img(img.rows, img.cols, CV_8UC3);
  
  img.copyTo(noisy_img);
  rng.fill(noise, cv::RNG::UNIFORM, 0, 1.0);

  for (int i = 0; i < noise.rows; i++) {
    for (int j = 0; j < noise.cols; j++) {
      if (noise.at<float>(cv::Point(j, i)) < probability) {
        float y = rng.uniform(0.0f, 1.0f) * 255;
        cv::Vec3b& colour = noisy_img.at<cv::Vec3b>(cv::Point(j, i));
        colour[0] = y;
        colour[1] = y;
        colour[2] = y;
      }
    }
  }

  cv::imshow(WINDOW_NAME, noisy_img);
  cv::imwrite("noisy_img.jpg", noisy_img);
  cv::waitKey(1);
  std::system("pause");

  std::cout << "Blurring the image with a 3x3 box kernel..." << std::endl;

  cv::Mat box_img(img.rows, img.cols, CV_8UC3);
  cv::Size box_kernel(3, 3);

  cv::blur(noisy_img, box_img, box_kernel);
  cv::imshow(WINDOW_NAME, box_img);
  cv::imwrite("box_img.jpg", box_img);

  cv::waitKey(1);
  std::system("pause");

  std::cout << "Taking a sample..." << std::endl;

  cv::Point sample_point(120, 60);
  
  int box_sample_matrix[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int img_sample_matrix[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  for (int i = sample_point.x - 1, count = 0; i <= sample_point.x + 1; i++)
    for (int j = sample_point.y - 1; j <= sample_point.y + 1; j++) {
      box_sample_matrix[count] = (uchar) box_img.at<cv::Vec3b>(cv::Point(j, i))[0];
      img_sample_matrix[count++] = (uchar) img.at<cv::Vec3b>(cv::Point(j, i))[0];
    }

  std::cout << "Original image sample 3x3 blue channel:" << std::endl;
  std::cout << std::setfill(' ') << std::setw(3) << img_sample_matrix[0] << " " << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[1] << " " << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[2] << std::endl;
  std::cout << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[3] << " " << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[4] << " " << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[5] << std::endl;
  std::cout << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[6] << " " << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[7] << " " << std::setfill(' ') << std::setw(3) <<  img_sample_matrix[8] << std::endl;

  std::cout << "Box blur sample 3x3 blue channel:" << std::endl;
  std::cout << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[0] << " " << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[1] << " " << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[2] << std::endl;
  std::cout << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[3] << " " << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[4] << " " << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[5] << std::endl;
  std::cout << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[6] << " " << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[7] << " " << std::setfill(' ') << std::setw(3) <<  box_sample_matrix[8] << std::endl;

  cv::waitKey(1);
  std::system("pause");

  std::cout << "Filtering the image with a 3x3 bilinear filter..." << std::endl;

  cv::Mat bilinear_img(img.rows, img.cols, CV_8UC3);
  
  cv::Matx<float, 3, 3> bilinear_kernel = 1 / 16.0f * cv::Matx<float, 3, 3>::Matx(1, 2, 1, 2, 4, 2, 1, 2, 1);

  cv::filter2D(noisy_img, bilinear_img, -1, bilinear_kernel);
  cv::imshow(WINDOW_NAME, bilinear_img);
  cv::imwrite("bilinear_img.jpg", bilinear_img);
  cv::waitKey(1);
  std::system("pause");

  std::cout << "Removing the noise with a median filter..." << std::endl;

  cv::Mat median_img(img.rows, img.cols, CV_8UC3);

  cv::medianBlur(noisy_img, median_img, 3);
  cv::imshow(WINDOW_NAME, median_img);
  cv::imwrite("median_img.jpg", median_img);
  cv::waitKey(1);
  std::system("pause");

  return 0;
}