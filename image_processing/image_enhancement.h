#ifndef IMAGE_ENHANCEMENT_H
#define IMAGE_ENHANCEMENT_H
#include "QVector"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "common.h"
#include <QtCore/qmath.h> 
using namespace cv;
class ImageEnhancement
{
public:
	ImageEnhancement();
	~ImageEnhancement();
	Common common;
	void linearTrans(Mat &img, float grid, float bias);
	void pieceWiseTrans(Mat &img, QVector<int> xRange,  QVector<float> grad, QVector<float> bias);
	void nonLinearExpTrans(Mat &img, float a, float b, float c);
	void nonLinearLogTrans(Mat &img, float c);
	void nonLinearGamaTrans(Mat &img, float gama, float c);
	void histEquTrans(Mat &img);
	void histSpecTrans(Mat &img, float b_spec[], float g_spec[], float r_spec[]);
	int piecewiseTransSplit(int r, QVector<int> xRange, QVector<float> grad, QVector<float> bias);
	int exp(int r, float a, float b, float c);
	void getHistOfImg(Mat img, float b[], float g[], float r[], int L);
	void getEqu(float s[]);
	void histSpecGMLTrans(Mat &img, float b_spec[], float g_spec[], float r_spec[]);
private:

};


#endif