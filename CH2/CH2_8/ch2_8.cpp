#include <iostream>
#include "opencv2/opencv.hpp"

void wave(const cv::Mat image, cv::Mat& result);

int main() {
	cv::Mat image = cv::imread("..\\resources\\boldt.png");
	cv::Mat result;
	cv::imshow("ima1", image);
	wave(image, result);
	cv::imshow("ima2", result);

	cv::waitKey(0);
}

void wave(const cv::Mat image, cv::Mat& result) {
	cv::Mat srcX(image.size(), CV_32F);
	cv::Mat srcY(image.size(), CV_32F);

	for (int i = 0; i < image.rows; i++)
	{
		/*for (int j = 0; j < image.cols; j++) {
			srcX.at<float>(i, j) = j;
			srcY.at<float>(i, j) = i + 3 * sin(j / 5);
		}*/
		float* dataX = srcX.ptr<float>(i);
		float* dataY = srcY.ptr<float>(i);
		for (int j = 0; j < image.cols; j++) {
			dataX[i, j] = j;
			dataY[i, j] = i + 3 * sin(j / 4);
		}

	}

	cv::remap(image, result, srcX, srcY, cv::INTER_LINEAR);
}