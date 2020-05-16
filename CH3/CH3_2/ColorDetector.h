#pragma once
#include "opencv2/opencv.hpp"

class ColorDetector
{
public:
	ColorDetector();
	ColorDetector(uchar blue, uchar green, uchar red, int maxDist);
	//设置颜色差距的阈值
	//阈值必须是正数，否则就设为0
	void setColorDistanceThreshhold(int distance);
	//取得颜色差距的阈值
	int getColorDistanceThreshold() const;
	//设置需要检测的颜色
	void setTargetColor(uchar blue, uchar green, uchar red);
	//设置需要检测的颜色
	void setTargetColor(cv::Vec3b color);
	//取得需要检测的颜色
	cv::Vec3b getTargetColor();
	//处理算法
	cv::Mat process1(const cv::Mat image);
	cv::Mat process2(const cv::Mat image);
	cv::Mat operator()(const cv::Mat image);
	//计算与目标颜色的距离
	int getDistanceToTargetColor(const cv::Vec3b color);
	//计算两个颜色之间的城区距离
	int getColorDistance(const cv::Vec3b color1, const cv::Vec3b color2);
private:
	//允许的最小差距
	int maxDist;
	//目标颜色
	cv::Vec3b target;
	//存储二值映像结果的图像
	cv::Mat result;


};

