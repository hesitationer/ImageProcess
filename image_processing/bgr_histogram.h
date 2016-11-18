#ifndef BGR_HISTOGRAM_H
#define BGR_HISTOGRAM_H
#include <QDialog>
#include <QPainter>
class BgrHistogram : public QDialog
{
	
public:
	BgrHistogram(QWidget *parent, float b[], float g[], float r[], QString title);
	~BgrHistogram();

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	float b[256];
	float g[256];
	float r[256];
};


#endif