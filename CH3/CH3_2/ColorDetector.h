#pragma once
#include "opencv2/opencv.hpp"

class ColorDetector
{
public:
	ColorDetector();
	ColorDetector(uchar blue, uchar green, uchar red, int maxDist);
	//������ɫ������ֵ
	//��ֵ�������������������Ϊ0
	void setColorDistanceThreshhold(int distance);
	//ȡ����ɫ������ֵ
	int getColorDistanceThreshold() const;
	//������Ҫ������ɫ
	void setTargetColor(uchar blue, uchar green, uchar red);
	//������Ҫ������ɫ
	void setTargetColor(cv::Vec3b color);
	//ȡ����Ҫ������ɫ
	cv::Vec3b getTargetColor();
	//�����㷨
	cv::Mat process1(const cv::Mat image);
	cv::Mat process2(const cv::Mat image);
	cv::Mat operator()(const cv::Mat image);
	//������Ŀ����ɫ�ľ���
	int getDistanceToTargetColor(const cv::Vec3b color);
	//����������ɫ֮��ĳ�������
	int getColorDistance(const cv::Vec3b color1, const cv::Vec3b color2);
private:
	//�������С���
	int maxDist;
	//Ŀ����ɫ
	cv::Vec3b target;
	//�洢��ֵӳ������ͼ��
	cv::Mat result;


};

