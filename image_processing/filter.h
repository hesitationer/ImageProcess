#ifndef FILTER_H
#define FILTER_H
#include "image_enhancement.h"
#include "hsi.h"
#include "common.h"
class Filter
{
public:
	Filter();
	~Filter();
	void lomo(Mat &img, Mat overlay);
	void grayscaleRelief(Mat &img);
	void pencilDrawing(Mat &img);
	void film(Mat &img);
private:
	ImageEnhancement imageEnhancement;
	Hsi hsi;
	Common common;
};


#endif