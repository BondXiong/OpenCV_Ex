#include <iostream>
#include "opencv2/opencv.hpp"

void colorReduce(cv::Mat image, int div);

int main() {
	cv::Mat image = cv::imread("..\\resources\\boldt.png");
	if (!image.empty()) {
		cv::imshow("ima1", image);
		colorReduce(image, 8);
		cv::imshow("ima2", image);
	}
	cv::waitKey(0);
}

void colorReduce(cv::Mat image, int div) {
	int n = log(div) / log(2);
	uchar mask = 0xFF << n;
	uchar divH = div >> 1;
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itE = image.end<cv::Vec3b>();
	while(it != itE) {
		(* it)[0] &= mask;
		(* it)[0] += divH;
		(* it)[1] &= mask;
		(* it)[1] += divH;
		(* it)[2] &= mask;
		(* it)[2] += divH;

		it++;
	}
}