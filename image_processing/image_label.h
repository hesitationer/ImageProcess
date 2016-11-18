#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPoint>
#include <QPainter>
#include <QRect>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
class Main_window;
class MyImageLabel : public QLabel
{
	Q_OBJECT
public:
	MyImageLabel();
	MyImageLabel(const QString &str, QWidget *parent);
	~MyImageLabel();

	Main_window *window;
	bool scribbling = false;
	bool move = false;
	int draw_flag = 0;
	int polygon_flag = 0;
	int width = 0;
	int height = 0;
	QPoint startPoint;
	QPoint endPoint;
	QPainter *painter;
	QVector<QPoint> points;

	void drawRect(QPoint start, QPoint end);
	void drawRound(QPoint start, QPoint end);
	void drawPolygon(QVector<QPoint> points, int flag); //flag = 1¶à±ßÐÎ·â±Õ


protected:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	//void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;


private:

};


#endif