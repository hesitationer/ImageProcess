#ifndef ROTATION_H
#define ROTATION_H

#include "ui_image_processing.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
class Rotation
{
public:
	Rotation();
	~Rotation();

	void rotation_image(Mat &img, bool left, int degree);
	void flipHorizontal(Mat &img);
	void flipVertical(Mat &img);
	void rotate90(Mat &img);
	void rotate180(Mat &img);
	double round(double r);


private:

};


#endif