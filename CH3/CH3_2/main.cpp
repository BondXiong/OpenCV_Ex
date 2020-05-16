#include "opencv2/opencv.hpp"
#include "ColorDetector.h"

int main() {
	//����ͼ�������
	ColorDetector cd;
	//��ȡ�����ͼ��
	cv::Mat image = cv::imread("..\\..\\resources\\boldt.png");
	if (image.empty()) return 0;
	cv::imshow("ima1", image);
	//�����������
	cd.setTargetColor(161, 161, 161);
	cd.setColorDistanceThreshhold(80);
	//����ͼ����ʾ���
	cv::Mat result = cd.process1(image);
	cv::imshow("ima2", result);
	cv::Mat result2 = cd.process2(image);
	cv::imshow("ima3", result2);
	cv::Mat result3;
	image.copyTo(result3);
	cv::floodFill(result3,
		cv::Point(100, 50),
		cv::Scalar(255, 255, 255),
		(cv::Rect*)0,
		cv::Scalar(20, 20, 20),
		cv::Scalar(20, 20, 20),
		cv::FLOODFILL_FIXED_RANGE);
	cv::imshow("ima4", result3);
	cv::Mat result4 = cd(image);
	cv::imshow("ima5", result4);
	cv::waitKey(0);
	return 0;
}