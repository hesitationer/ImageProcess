#ifndef HSI_H
#define HSI_H
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
class Hsi
{
public:
	Hsi();
	~Hsi();
	void changeLight(Mat &img, int value);
	void changeSaturation(Mat &img, int value);
	void changeTone(Mat &img, int value);
	void bgr2hsi(Mat &bgr, Mat &hsi);
	void hsi2bgr(Mat &hsi, Mat &bgr);
private:

};

#endif