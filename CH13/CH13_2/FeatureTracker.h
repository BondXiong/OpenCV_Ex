#pragma once
#include "FrameProcessor.h"
#include "opencv2/opencv.hpp"
class FeatureTracker :
	public FrameProcessor
{
public:
	FeatureTracker();
	void process(cv::Mat& frame, cv::Mat& output);
	//�ж��Ƿ���Ҫ����µ�������
	bool addNewPoints();
	//�ж���Ҫ������������
	bool acceptTrackedPoint(int i);
	//����ǰ���ٵ�������
	void handleTrackedPoints(cv::Mat& frame, cv::Mat& output);
	//�������ⷽ��
	void detectFeaturePoints();
private:
	cv::Mat gray;
	cv::Mat grayPrev;
	std::vector<cv::Point2f> points[2];
	std::vector<cv::Point2f> initial;
	std::vector<cv::Point2f> features;
	int max_count;
	double qlevel;
	double minDist;
	std::vector<uchar> status;
	std::vector<float> err;
};

