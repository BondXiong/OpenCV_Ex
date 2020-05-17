// CH1.3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "opencv2/opencv.hpp"
//#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

void onMouse(int event, int x, int y, int flags, void* param);

int main()
{
	cv::Mat image1;
	cv::Mat resultH;
	cv::Mat resultV;
	cv::Mat resultH_V;
	std::cout << "image1.row:" << image1.rows << std::endl;
	std::cout << "image1.col:" << image1.cols << std::endl;
	image1 = cv::imread("..\\resources\\CH1.3_dog.png");
	//image1 = cv::imread("F:\\VisualStudio\\VSWorkSpace\\resources\\CH1.3_dog.png"); 
	
	cv::circle(image1, cv::Point(215, 150), 65, 0, 3);
	cv::putText(image1, "This is a dog.", cv::Point(120, 280), cv::FONT_HERSHEY_PLAIN, 2.0, 0, 2);


	if (image1.empty()) {
		std::cout << "Load picture error!" << std::endl;
	}
	else
	{
		//正数表示水平
		//0表示垂直
		//负数表示水平和垂直
		cv::flip(image1, resultH, 1);
		cv::flip(image1, resultV, 0);
		cv::flip(image1, resultH_V, -1);

		cv::namedWindow("original image");
		cv::namedWindow("resultH image");
		cv::namedWindow("resultV image");
		cv::namedWindow("resultH_V image");

		cv::imshow("original image", image1);
		cv::imshow("resultH image", resultH);
		cv::imshow("resultV image", resultV);
		cv::imshow("resultH_V image", resultH_V);
	}
	
	cv::setMouseCallback("original image", onMouse, reinterpret_cast<void *>(&image1));

	//0---永远的等待按键
	//正数---等待的毫秒数
	cv::waitKey(0);

}

void onMouse(int event, int x, int y, int flags, void* param) {
	cv::Mat* im = reinterpret_cast<cv::Mat*>(param);
	switch (event) {
	case cv::EVENT_FLAG_LBUTTON:
		std::cout << "at (" << x << " " << y << ") value is：" 
			<< static_cast<int>(im->at<uchar>(cv::Point(x, y)))<<std::endl;
		break;
	}
}
