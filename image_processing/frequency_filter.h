#ifndef FREQUENCY_FILTER_H
#define FREQUENCY_FILTER_H
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <algorithm>
#include "common.h"
#include "image_enhancement.h"

using namespace cv;
using namespace std;

class FrequencyFilter{

private :
	Common common;
	ImageEnhancement imageEnhancement;
public:
	FrequencyFilter();
	~FrequencyFilter();

	void blur(Mat &img, int n, float d0);
	void sharpen(Mat &img, int n, int d0, float a);
	void createButterworthLowpassFilter(Mat &dft_Filter, int d0, int n, bool low, float a);
	//void shiftDFT(Mat &fImage);
	void doDft(Mat &img, int n, float d0, bool low, float a);


};
#endif