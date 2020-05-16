#include "VideoProcessor.h"
#include "FeatureTracker.h"
int main() {
	VideoProcessor processor;
	FeatureTracker tracker;
	processor.setInput("..\\..\\resources\\ch13_2.mp4");
	processor.setFrameProcessor(&tracker);
	processor.displayOutput("Tracked Features");
	processor.setDelay(1000 / processor.getFrameRate());
	processor.run();
}