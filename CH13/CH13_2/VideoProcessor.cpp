#include "VideoProcessor.h"
#include <iostream>
void VideoProcessor::setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&, cv::Mat&)) {
	process = frameProcessingCallback;
	setCallIt(true);
}
void VideoProcessor::setFrameProcessor(FrameProcessor* frameProcessorPtr) {
	process = 0;
	mFrameProcessor = frameProcessorPtr;
	setCallIt(true);

}
bool VideoProcessor::setInput(std::string fileName) {
	fnumber = 0;
	capture.release();
	return capture.open(fileName);
}
bool VideoProcessor::setInput(const std::vector<std::string>& img) {
	fnumber = 0;
	capture.release();
	images = img;
	itImg = images.begin();
	return true;
}
//设置输出视频文件
bool VideoProcessor::setOutput(const std::string filename, int codec,
				double frameRate, bool isColor) {
	outputFile = filename;
	extension.clear();
	if (frameRate == 0) frameRate = getFrameRate();
	char c[4];
	if (codec == 0) codec = getCodec(c);
	return writer.open(outputFile,
						codec,
						frameRate,
						getFrameSize(),
						isColor);
}
//写输出的帧
//可以是视频文件或图像组
void VideoProcessor::writeNextFrame(cv::Mat& frame) {
	if (extension.length()) {
		std::stringstream ss;
		ss << outputFile << std::setfill('0') << std::setw(digits) << currentIndex++ << extension;
		cv::imwrite(ss.str(), frame);
	} else {
		writer.write(frame);
	}
}
//设置输出为一系列图像文件
//扩展名必须是.jpg或.bmp
bool VideoProcessor::setOutput(const std::string& filename,	//前缀
								const std::string& ext,		//扩展名
								int numberOfDigits,			//数字的位数
								int startIndex) {			//开始序号
	if (numberOfDigits < 0) return false;
	outputFile = filename;
	extension = ext;
	digits = numberOfDigits;
	currentIndex = startIndex;
	return true;
}
void VideoProcessor::displayInput(std::string wn) {
	windowNameInput = wn;
	cv::namedWindow(windowNameInput);
}
void VideoProcessor::displayOutput(std::string wn) {
	windowNameOutput = wn;
	cv::namedWindow(windowNameOutput);
}
void VideoProcessor::run() {
	cv::Mat frame;
	cv::Mat output;
	if (!isOpened()) return;
	stop = false;
	while (!isStopped())
	{
		if (!readNextFrame(frame)) break;
		if (windowNameInput.length() != 0) cv::imshow(windowNameInput, frame);
		if (callIt) {
			if (process)
				process(frame, output);
			else if (mFrameProcessor)
				mFrameProcessor->process(frame, output);
			fnumber++;
		}
		else {
			output = frame;
		}
		/*写入到输出的序列*/
		if (outputFile.length() != 0) writeNextFrame(output);
		if (windowNameOutput.length() != 0) cv::imshow(windowNameOutput, output);
		if (delay >= 0 && cv::waitKey(delay) >= 0) stopIt();
		if (frameToStop >= 0 && getFrameNumber() == frameToStop) stopIt();
	}
}
void VideoProcessor::setCallIt(bool t) {
	callIt = t;
}

void VideoProcessor::stopIt() {
	stop = true;
}
bool VideoProcessor::isStopped() {
	return stop;
}
bool VideoProcessor::isOpened() {
	return capture.isOpened() || !images.empty();
}
void VideoProcessor::setDelay(int d) {
	delay = d;
}
void VideoProcessor::setFrameToStop(long d) {
	frameToStop = d;
}

long VideoProcessor::getFrameNumber() {
	return fnumber;
}
int VideoProcessor::getFrameRate() {
	return capture.get(cv::CAP_PROP_FPS);
}
int VideoProcessor::getCodec(char c[4]) {
	if (images.size() != 0) return -1;
	union {
		int value;
		char node[4];
	} returned;
	returned.value = static_cast<int>(capture.get(cv::CAP_PROP_FOURCC));
	c[0] = returned.node[0];
	c[1] = returned.node[1];
	c[2] = returned.node[2];
	c[3] = returned.node[3];
	return returned.value;
}
cv::Size VideoProcessor::getFrameSize() {
	//if (images.size() != 0) return -1;
	double wid = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double hei = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	return cv::Size(wid, hei);
}

bool VideoProcessor::readNextFrame(cv::Mat& frame) {
	//capture >> frame;
	//capture.grab();
	//capture.retrieve(frame);
	if (images.size() == 0) {
		return capture.read(frame);
	}
	else {
		if (itImg != images.end()) {
			frame = cv::imread(*itImg);
			itImg++;
			return frame.data != 0;
		}
		else
			return false;
	}
	
}