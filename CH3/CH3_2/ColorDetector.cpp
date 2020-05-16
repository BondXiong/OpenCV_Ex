#include "ColorDetector.h"
//���캯��
ColorDetector::ColorDetector() :maxDist(100), target(0, 0, 0) {}
ColorDetector::ColorDetector(uchar blue, uchar green, uchar red, int maxDist) {
	setColorDistanceThreshhold(maxDist);
	setTargetColor(blue, green, red);
}
//������ɫ������ֵ
//��ֵ�������������������Ϊ0
void ColorDetector::setColorDistanceThreshhold(int distance) {
	if (distance < 0)
		distance = 0;
	this->maxDist = distance;
}
//ȡ����ɫ������ֵ
int ColorDetector::getColorDistanceThreshold() const {
	return this->maxDist;
}
//������Ҫ������ɫ
void ColorDetector::setTargetColor(uchar blue, uchar green, uchar red) {
	//����ΪBGR
	this->target = cv::Vec3b(blue, green, red);
}
//������Ҫ������ɫ
void ColorDetector::setTargetColor(cv::Vec3b color) {
	this->target = color;
}
//ȡ����Ҫ������ɫ
cv::Vec3b ColorDetector::getTargetColor() {
	return this->target;
}
//�����㷨
cv::Mat ColorDetector::process1(const cv::Mat image) {
	//��Ҫʱ�ط����ֵͼ��
	//������ͼ��ĳߴ���ͬ�������ǵ�ͨ��
	result.create(image.size(), CV_8U);
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itE = image.end<cv::Vec3b>();
	cv::Mat_<uchar>::iterator itR = result.begin<uchar>();
	//����ÿ������
	for ( ; it < itE; ++it, ++itR)
	{
		if (getDistanceToTargetColor(*it) < maxDist) {
			*itR = 255;
		} else {
			*itR = 0;
		}
	}
	return result;
}
cv::Mat ColorDetector::process2(const cv::Mat image) {
	cv::Mat output;
	//������Ŀ����ɫ�ľ���ľ���ֵ
	cv::absdiff(image, cv::Scalar(target), output);
	//��ͨ���ָ������ͼ��
	std::vector<cv::Mat> images;
	cv::split(output, images);
	//3��ͨ�����
	output = images[0] + images[1] + images[2];
	//Ӧ����ֵ
	cv::threshold(output, output, maxDist, 255, cv::THRESH_BINARY_INV);

	return output;
}
cv::Mat ColorDetector::operator()(const cv::Mat image) {
	cv::Mat output;
	//������Ŀ����ɫ�ľ���ľ���ֵ
	cv::absdiff(image, cv::Scalar(target), output);
	//��ͨ���ָ������ͼ��
	std::vector<cv::Mat> images;
	cv::split(output, images);
	//3��ͨ�����
	output = images[0] + images[1] + images[2];
	//Ӧ����ֵ
	cv::threshold(output, output, maxDist, 255, cv::THRESH_BINARY_INV);

	return output;
}
//������Ŀ����ɫ�ľ���
int ColorDetector::getDistanceToTargetColor(const cv::Vec3b color) {
	return getColorDistance(color, this->target);
}
//����������ɫ֮��ĳ�������
int ColorDetector::getColorDistance(const cv::Vec3b color1, const cv::Vec3b color2) {
	return abs(color1[0] - color2[0]) +
		abs(color1[1] - color2[1]) +
		abs(color1[2] - color2[2]);
}