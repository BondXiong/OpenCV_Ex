#pragma once
#include "FrameProcessor.h"
#include "opencv2/opencv.hpp"
class FeatureTracker :
	public FrameProcessor
{
public:
	FeatureTracker();
	void process(cv::Mat& frame, cv::Mat& output);
	//判断是否需要添加新的特征点
	bool addNewPoints();
	//判断需要保留的特征点
	bool acceptTrackedPoint(int i);
	//处理当前跟踪的特征点
	void handleTrackedPoints(cv::Mat& frame, cv::Mat& output);
	//特征点检测方法
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

