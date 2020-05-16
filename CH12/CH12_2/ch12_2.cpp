#include "opencv2/opencv.hpp"
#include <iostream>

int main() {
	//打开视频文件
	cv::VideoCapture vc("..\\..\\resources\\ace.mp4");
	//检查视频是否成功打开
	if (!vc.isOpened()) return -1;
	//取得帧速率
	double rate = vc.get(cv::CAP_PROP_FPS);
	std::cout << rate << std::endl;

	bool stop(false);
	cv::Mat frame;
	
	int delay = 1000 / rate;
	while (!stop) {
		
		//读取下一帧
		if (!vc.read(frame)) break;
		cv::imshow("frame", frame);
		
		if (cv::waitKey(delay) >= 0) stop = true;
	}
	vc.release();
	return 0;
}