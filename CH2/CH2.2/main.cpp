#include <iostream>
#include <random>
#include "opencv2/opencv.hpp"

void salt(cv::Mat image, int n);

int main() {
	cv::Mat image = cv::imread("..\\resources\\boldt.png");
	if(image.empty() != true)
	cv::imshow("ima1", image);
	salt(image, 10);
	cv::imshow("ima2", image);
	cv::waitKey(0);
}

void salt(cv::Mat image, int n) {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
	std::uniform_int_distribution<int> randomCol(0, image.cols - 1);
	int i, j;
	for (int k = 0; k < n; k++)
	{
		i = randomCol(generator);
		j = randomRow(generator);
		if (image.type() == CV_8UC1) {
			image.at<uchar>(j, i) = 255;
		}
		else if (image.type() == CV_8UC3){
			//image.at<cv::Vec3b>(j, i)[0] = 255;
			//image.at<cv::Vec3b>(j, i)[1] = 255;
			//image.at<cv::Vec3b>(j, i)[2] = 255;
			image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
		}
	}
}