#include "ColorDetector.h"
//构造函数
ColorDetector::ColorDetector() :maxDist(100), target(0, 0, 0) {}
ColorDetector::ColorDetector(uchar blue, uchar green, uchar red, int maxDist) {
	setColorDistanceThreshhold(maxDist);
	setTargetColor(blue, green, red);
}
//设置颜色差距的阈值
//阈值必须是正数，否则就设为0
void ColorDetector::setColorDistanceThreshhold(int distance) {
	if (distance < 0)
		distance = 0;
	this->maxDist = distance;
}
//取得颜色差距的阈值
int ColorDetector::getColorDistanceThreshold() const {
	return this->maxDist;
}
//设置需要检测的颜色
void ColorDetector::setTargetColor(uchar blue, uchar green, uchar red) {
	//次序为BGR
	this->target = cv::Vec3b(blue, green, red);
}
//设置需要检测的颜色
void ColorDetector::setTargetColor(cv::Vec3b color) {
	this->target = color;
}
//取得需要检测的颜色
cv::Vec3b ColorDetector::getTargetColor() {
	return this->target;
}
//处理算法
cv::Mat ColorDetector::process1(const cv::Mat image) {
	//必要时重分配二值图像
	//与输入图像的尺寸相同，不过是单通道
	result.create(image.size(), CV_8U);
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itE = image.end<cv::Vec3b>();
	cv::Mat_<uchar>::iterator itR = result.begin<uchar>();
	//遍历每个像素
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
	//计算与目标颜色的距离的绝对值
	cv::absdiff(image, cv::Scalar(target), output);
	//把通道分割进三幅图像
	std::vector<cv::Mat> images;
	cv::split(output, images);
	//3个通道相加
	output = images[0] + images[1] + images[2];
	//应用阈值
	cv::threshold(output, output, maxDist, 255, cv::THRESH_BINARY_INV);

	return output;
}
cv::Mat ColorDetector::operator()(const cv::Mat image) {
	cv::Mat output;
	//计算与目标颜色的距离的绝对值
	cv::absdiff(image, cv::Scalar(target), output);
	//把通道分割进三幅图像
	std::vector<cv::Mat> images;
	cv::split(output, images);
	//3个通道相加
	output = images[0] + images[1] + images[2];
	//应用阈值
	cv::threshold(output, output, maxDist, 255, cv::THRESH_BINARY_INV);

	return output;
}
//计算与目标颜色的距离
int ColorDetector::getDistanceToTargetColor(const cv::Vec3b color) {
	return getColorDistance(color, this->target);
}
//计算两个颜色之间的城区距离
int ColorDetector::getColorDistance(const cv::Vec3b color1, const cv::Vec3b color2) {
	return abs(color1[0] - color2[0]) +
		abs(color1[1] - color2[1]) +
		abs(color1[2] - color2[2]);
}