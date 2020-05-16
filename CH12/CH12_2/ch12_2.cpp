#include "opencv2/opencv.hpp"
#include <iostream>

int main() {
	//����Ƶ�ļ�
	cv::VideoCapture vc("..\\..\\resources\\ace.mp4");
	//�����Ƶ�Ƿ�ɹ���
	if (!vc.isOpened()) return -1;
	//ȡ��֡����
	double rate = vc.get(cv::CAP_PROP_FPS);
	std::cout << rate << std::endl;

	bool stop(false);
	cv::Mat frame;
	
	int delay = 1000 / rate;
	while (!stop) {
		
		//��ȡ��һ֡
		if (!vc.read(frame)) break;
		cv::imshow("frame", frame);
		
		if (cv::waitKey(delay) >= 0) stop = true;
	}
	vc.release();
	return 0;
}