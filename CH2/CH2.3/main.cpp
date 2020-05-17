#include <iostream>
#include "opencv2\opencv.hpp"

void colorReduce(const cv::Mat image, cv::Mat &result, int n);

int main() {
	cv::Mat image = cv::imread("..\\resources\\boldt.png", cv::IMREAD_GRAYSCALE);
	cv::Mat result;
	cv::imshow("ima1", image);
	colorReduce(image, result, 10);
	cv::imshow("ima2", image);
	cv::imshow("ima3", result);
	cv::waitKey(0);
}

void colorReduce(const cv::Mat image, cv::Mat &result, int n = 64) {
	result.create(image.rows, image.cols, image.type());
	if (image.isContinuous()) {
		image.reshape(1, 1);
	}
	int nl = image.rows;
	int nc = image.cols * image.channels();
	int nn = log(n) / log(2);
	std::cout << nn;
	/*if (image.isContinuous()) {
		nc *= nl;
		nl = 1;
	}*/
	uchar mask = 0xFF << nn;
	for (int j = 0; j < nl; j++)
	{
		const uchar* dataIn = image.ptr<uchar>(j);
		uchar* data = result.ptr<uchar>(j);
		
		for (int i = 0; i < nc; i++)
		{
			//data[i] = data[i] / n * n + n / 2;
			//取模方式
			//data[i] = data[i] - data[i] % n + n / 2;
			//等效做法
			//*data++ = *data / n * n + n / 2;
			//使用位运算
			*data = *dataIn++ & mask;
			*data++ += nn >> 1;
		}
		
		
		//std::cout << div << std::endl;
	}
}