#pragma once
#include "opencv2/opencv.hpp"
class FrameProcessor
{
public:
	virtual void process(cv::Mat& input, cv::Mat& output) = 0;
};

