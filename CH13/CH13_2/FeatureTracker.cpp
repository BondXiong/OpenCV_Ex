#include "FeatureTracker.h"
#include <iostream>
FeatureTracker::FeatureTracker() : max_count(500), qlevel(0.01), minDist(10.) {};
void FeatureTracker::process(cv::Mat& frame, cv::Mat& output) {
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
	frame.copyTo(output);
	if (addNewPoints()) {
		//���������
		detectFeaturePoints();
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}
	//���������еĵ�һ��ͼ��
	if (grayPrev.empty()) {
		gray.copyTo(grayPrev);
		//��������
		cv::calcOpticalFlowPyrLK(grayPrev, gray,
								points[0],
								points[1],
								status,
								err);
		int k = 0;
		for (int i = 0; i < points[1].size(); i++) {
			//�Ƿ������������
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
	//�ж��Ƿ���Ҫ����µ�������
	bool FeatureTracker::addNewPoints() {
		return points[0].size() <= 10;
	}
	//�ж���Ҫ������������
	bool FeatureTracker::acceptTrackedPoint(int i) {
		return status[i] && (abs(points[0][i].x - points[1][i].x)
					+ (abs(points[0][i].y - points[1][i].y)) > 2);
	}
	//����ǰ���ٵ�������
	void FeatureTracker::handleTrackedPoints(cv::Mat& frame, cv::Mat& output) {
		for (int i = 0; i < points[1].size(); i++) {
			std::cout << "sdf" << std::endl;
			cv::line(output, initial[i], points[1][i], cv::Scalar(255, 255, 255));
			cv::circle(output, points[1][i], 3, cv::Scalar(255, 255, 255), -1);
		}
	}
	//�������ⷽ��
	void FeatureTracker::detectFeaturePoints() {
		cv::goodFeaturesToTrack(gray,
								features,
								max_count,
								qlevel,
								minDist);
	}
