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
	//���������Ƶ�ļ�
	bool setOutput(const std::string filename, int codec = 0, 
					double frameRate = 0.0, bool isColor = true);
	//д�����֡
	//��������Ƶ�ļ���ͼ����
	void writeNextFrame(cv::Mat& frame);
	//�������Ϊһϵ��ͼ���ļ�
	//��չ��������.jpg��.bmp
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
	//OpenCV��Ƶ�������
	cv::VideoCapture capture;
	//��Ϊ��������ͼ���ļ�������
	std::vector<std::string> images;
	//ͼ�������ĵ�����
	std::vector<std::string>::const_iterator itImg;
	//д��Ƶ����
	cv::VideoWriter writer;
	//��Ա֡������
	FrameProcessor *mFrameProcessor;
	//����ÿһ֡ʱ������õĻص�����
	void (*process)(cv::Mat&, cv::Mat&);
	//��ʾ�ûص������Ƿ�ᱻ����
	bool callIt;
	//���봰������
	std::string windowNameInput;
	//�����������
	std::string windowNameOutput;
	//֮֡�����ʱ
	int delay;
	//�Ѿ������֡��
	long fnumber;
	//�ﵽ���֡��ʱ����
	long frameToStop;
	//��������
	bool stop;

	//����ļ���
	std::string outputFile;
	//���ͼ��ĵ�ǰ���
	int currentIndex;
	//���ͼ���ļ��������ֵ�λ��
	int digits;
	//���ͼ�����չ��
	std::string extension;

	bool readNextFrame(cv::Mat& frame);
};

