#include <iostream>
#include "opencv2/opencv.hpp"

void colorReduce(cv::Mat image, cv::Mat& result, int div);

int main() {
	cv::Mat image = cv::imread("..\\resources\\boldt.png");
	cv::Mat imageAdd = cv::imread("..\\resources\\rain.png");
	cv::Mat result1, result2, result3;
	std::vector<cv::Mat> planes;
	cv::imshow("ima1", image);
	cv::imshow("ima2", imageAdd);

	cv::addWeighted(image, 0.7, imageAdd, 0.9, 0, result1);
	cv::imshow("ima3", result1);

	colorReduce(image, result2, 64);
	cv::imshow("ima4", result2);

	cv::split(image, planes);
	cv::cvtColor(imageAdd, imageAdd, cv::COLOR_BGR2GRAY);
	planes[0] += imageAdd;
	cv::merge(planes, result3);
	cv::imshow("ima4", result3);
	cv::waitKey(0);
}

void colorReduce(cv::Mat image, cv::Mat& result, int div) {
	result.create(image.size(), image.type());
	int n = static_cast<int>(log(div) / log(2) + 0.5);
	uchar mask = 0xFF << n;
	int divH = div >> 1;

	result = image & cv::Scalar(mask, mask, mask) + cv::Scalar(divH, divH, divH);

}