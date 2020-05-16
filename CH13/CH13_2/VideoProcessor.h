#pragma once
#include <string>
#include "opencv2/opencv.hpp"
#include "FrameProcessor.h"
class VideoProcessor
{
public:
	void setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&, cv::Mat&));
	void setFrameProcessor(FrameProcessor* frameProcessorPtr);
	bool setInput(std::string fileName);
	bool setInput(const std::vector<std::string>& img);
	//设置输出视频文件
	bool setOutput(const std::string filename, int codec = 0, 
					double frameRate = 0.0, bool isColor = true);
	//写输出的帧
	//可以是视频文件或图像组
	void writeNextFrame(cv::Mat& frame);
	//设置输出为一系列图像文件
	//扩展名必须是.jpg或.bmp
	bool setOutput(const std::string& filename,
					const std::string& ext,
					int numberOfDigits = 3,
					int startIndex = 0);
	void displayInput(std::string wn);
	void displayOutput(std::string wn);
	void run();
	void setCallIt(bool t);
	void stopIt();
	bool isStopped();
	bool isOpened();
	void setDelay(int d);
	void setFrameToStop(long d);
	
	long getFrameNumber();
	int getFrameRate();
	int getCodec(char c[4]);
	cv::Size getFrameSize();
private:
	//OpenCV视频捕获对象
	cv::VideoCapture capture;
	//作为输入对象的图像文件名向量
	std::vector<std::string> images;
	//图像向量的迭代器
	std::vector<std::string>::const_iterator itImg;
	//写视频对象
	cv::VideoWriter writer;
	//成员帧处理类
	FrameProcessor *mFrameProcessor;
	//处理每一帧时都会调用的回调函数
	void (*process)(cv::Mat&, cv::Mat&);
	//表示该回调函数是否会被调用
	bool callIt;
	//输入窗口名称
	std::string windowNameInput;
	//输出窗口名称
	std::string windowNameOutput;
	//帧之间的延时
	int delay;
	//已经处理的帧数
	long fnumber;
	//达到这个帧数时结束
	long frameToStop;
	//结束处理
	bool stop;

	//输出文件名
	std::string outputFile;
	//输出图像的当前序号
	int currentIndex;
	//输出图像文件名中数字的位数
	int digits;
	//输出图像的扩展名
	std::string extension;

	bool readNextFrame(cv::Mat& frame);
};

