#ifndef SPATIAL_FILTER_H
#define SPATIAL_FILTER_H
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <algorithm>
#include <cmath>
#include <common.h>
using namespace cv;
using namespace std;
class SpatialFilter
{
public:
	SpatialFilter();
	~SpatialFilter();
	void medianFilter(Mat &img, int template_size, bool **template_shape);
	void gaussianBlur(Mat &img, float sigma, int template_size);
	void sharpenRoberts(Mat &img, int threshold, int incremental);
	void sharpenPrewitt(Mat &img, int threshold, int incremental);
	void sharpenSobel(Mat &img, int threshold, int incremental);
	void sharpenLaplace(Mat &img, int threshold, int incremental);
	Common common;

private:

};


#endif