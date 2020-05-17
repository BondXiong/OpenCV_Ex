#include <iostream>
#include "opencv2/opencv.hpp"

void sharpen(const cv::Mat image, cv::Mat &result);
void sharpen2D(const cv::Mat image, cv::Mat& result);

int main() {
	cv::Mat image = cv::imread("..\\..\\resources\\boldt.png");
	cv::Mat result1;
	cv::Mat result2;
	cv::imshow("ima1", image);
	sharpen(image, result1);
	cv::imshow("ima2", result1);
	sharpen2D(image, result2);
	cv::imshow("ima3", result2);
	cv::waitKey(0);
}

void sharpen(const cv::Mat image, cv::Mat &result) {
	result.create(image.size(), image.type());
	int nchannels = image.channels();
	for (int i = 1; i < image.rows - 1; i++)
	{
		const uchar* previous = image.ptr<const uchar>(i - 1);
		const uchar* current = image.ptr<const uchar>(i);
		const uchar* next = image.ptr<const uchar>(i + 1);

		uchar* output = result.ptr<uchar>(i);

		for (int j = nchannels; j < (image.cols - 1) * nchannels; j++)
		{
			*output++ = cv::saturate_cast<uchar>(5 * current[j]
						- previous[j]
						- next[j]
						- current[j - nchannels]
						- current[j + nchannels]);
		}
	}
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void sharpen2D(const cv::Mat image, cv::Mat& result) {
	result.create(image.size(), image.type());
	cv::Mat kernel(3,3, CV_32F,	cv::Scalar(0));
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 1) = 5;

	cv::filter2D(image, result, image.depth(), kernel);
}