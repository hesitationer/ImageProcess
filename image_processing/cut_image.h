#ifndef CUT_IMAGE_H
#define CUT_IMAGE_H
#include <QPoint>
#include <QVector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
class CutImage
{
public:
	CutImage();
	~CutImage();
	void cutRect(Mat &img, int x, int y, int w, int h);
	void cutRound(Mat &img, QPoint center, int r);
	void cutPolygon(Mat &img, QVector<QPoint> points);
private:

};

#endif 