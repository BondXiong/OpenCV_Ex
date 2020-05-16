#include "opencv2/opencv.hpp"

cv::Mat test01();
cv::Mat test02(const cv::Mat image);
void detectColor(const cv::Mat image,
				double minHue, double maxHue,
				double minSat, double maxSat,
				cv::Mat& mask);

int main() {
	cv::Mat image = cv::imread("..\\..\\resources\\test1.jpg");
	cv::Mat imageHSV;
	if (image.empty()) return 0;
	cv::cvtColor(image, imageHSV, cv::COLOR_BGR2HSV);

	std::vector<cv::Mat> channels;
	cv::split(imageHSV, channels);
	cv::imshow("ima1", image);
	cv::imshow("Hue", channels[0]);
	cv::imshow("Saturation", channels[1]);
	cv::imshow("Value", channels[2]);

	cv::Mat hs = test01();
	cv::imshow("ima2", hs);

	cv::Mat newImage = test02(image);
	cv::imshow("ima3", newImage);

	cv::Mat image1 = cv::imread("..\\..\\resources\\liu.jpg");
	cv::imshow("ima4", image1);
	cv::Mat mask;
	detectColor(image1, 160, 10, 25, 166, mask);
	cv::Mat detected(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	image1.copyTo(detected,mask);
	cv::imshow("ima5", detected);
	cv::waitKey(0);
	return -1;
}

cv::Mat test01() {
	cv::Mat hs(128, 360, CV_8UC3);
	for (int h = 0; h < 360; h++)
	{
		for (int s = 0; s < 128; s++) {
			hs.at<cv::Vec3b>(s, h)[0] = h / 2;
			hs.at<cv::Vec3b>(s, h)[1] = 255 - s * 2;
			hs.at<cv::Vec3b>(s, h)[2] = 255;
		}
	}
	return hs;
}

cv::Mat test02(const cv::Mat image) {
	cv::Mat hsv;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	std::vector<cv::Mat> channels;
	cv::split(image, channels);
	channels[2] = 255;
	cv::merge(channels, hsv);
	cv::Mat newImage;
	cv::cvtColor(hsv, newImage, cv::COLOR_HSV2BGR);
	return newImage;
}

void detectColor(const cv::Mat image,
				double minHue, double maxHue,
				double minSat, double maxSat,
				cv::Mat& mask) {
	cv::Mat hsv;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	std::vector<cv::Mat> channels;
	cv::split(hsv, channels);
	//色调掩码
	cv::Mat mask1;
	cv::threshold(channels[0], mask1, maxHue, 255, cv::THRESH_BINARY_INV);
	cv::Mat mask2;
	cv::threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY);
	cv::Mat hueMask;
	if (minHue < maxHue)
		hueMask = mask1 & mask2;
	else
		hueMask = mask1 | mask2;
	//饱和度掩码
	cv::Mat satMask;
	cv::inRange(channels[1], minSat, maxSat, satMask);
	//组合掩码
	mask = hueMask & satMask;
}