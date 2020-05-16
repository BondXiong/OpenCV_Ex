#include "FeatureTracker.h"
#include <iostream>
FeatureTracker::FeatureTracker() : max_count(500), qlevel(0.01), minDist(10.) {};
void FeatureTracker::process(cv::Mat& frame, cv::Mat& output) {
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
	frame.copyTo(output);
	if (addNewPoints()) {
		//检测特征点
		detectFeaturePoints();
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}
	//对于序列中的第一幅图像
	if (grayPrev.empty()) {
		gray.copyTo(grayPrev);
		//跟踪特征
		cv::calcOpticalFlowPyrLK(grayPrev, gray,
								points[0],
								points[1],
								status,
								err);
		int k = 0;
		for (int i = 0; i < points[1].size(); i++) {
			//是否保留这个特征点
			if (acceptTrackedPoint(i)) {
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		points[1].resize(k);
		initial.resize(k);
		handleTrackedPoints(frame, output);
		std::swap(points[1], points[0]);
		cv::swap(grayPrev, gray);
	}

}
	//判断是否需要添加新的特征点
	bool FeatureTracker::addNewPoints() {
		return points[0].size() <= 10;
	}
	//判断需要保留的特征点
	bool FeatureTracker::acceptTrackedPoint(int i) {
		return status[i] && (abs(points[0][i].x - points[1][i].x)
					+ (abs(points[0][i].y - points[1][i].y)) > 2);
	}
	//处理当前跟踪的特征点
	void FeatureTracker::handleTrackedPoints(cv::Mat& frame, cv::Mat& output) {
		for (int i = 0; i < points[1].size(); i++) {
			std::cout << "sdf" << std::endl;
			cv::line(output, initial[i], points[1][i], cv::Scalar(255, 255, 255));
			cv::circle(output, points[1][i], 3, cv::Scalar(255, 255, 255), -1);
		}
	}
	//特征点检测方法
	void FeatureTracker::detectFeaturePoints() {
		cv::goodFeaturesToTrack(gray,
								features,
								max_count,
								qlevel,
								minDist);
	}
