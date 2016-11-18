#include "bgr_histogram.h"

BgrHistogram::BgrHistogram(QWidget *parent, float b[], float g[], float r[], QString title) : QDialog(parent)
{
	for (int i = 0; i < 256; i++)
	{
		this->b[i] = b[i];
		this->g[i] = g[i];
		this->r[i] = r[i];
	}
	resize(400, 400);
	setWindowTitle(title);
}

BgrHistogram::~BgrHistogram()
{
}

void BgrHistogram::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->drawText(200, 15, tr("b"));
	painter->drawText(200, 140, tr("g"));
	painter->drawText(200, 265, tr("r"));

	for (int i = 0; i < 3; i++)
	{
		painter->drawLine(72, 115 + i * 125, 328, 115 + i * 125);

		for (int j = 1; j <= 12; j++)
		{
			painter->drawText(72 + j * 20 - 5, 115 + i * 125 + 12, QString::number(j * 20));
		}

		painter->drawLine(72, 115 + i * 125, 72, 15 + i * 125 - 10);

		for (int j = 1; j <= 10; j++)
		{
			painter->drawText(72 - 40, 115 + i * 125 - j * 10 + 5, QString::number(j * 0.002));
			painter->drawLine(72, 115 + i * 125 - j * 10, 72 + 5, 115 + i * 125 - j * 10);
		}

		painter->drawLine(328 - 5, 115 + i * 125 - 5, 328, 115 + i * 125);
		painter->drawLine(328 - 5, 115 + i * 125 + 5, 328, 115 + i * 125);
		painter->drawLine(72 - 5, 15 + i * 125, 72, 15 + i * 125 - 10);
		painter->drawLine(72 + 5, 15 + i * 125, 72, 15 + i * 125 - 10);
	}

	for (int i = 0; i < 256; i++)
	{

		painter->drawLine(72 + i, 115, 72 + i, 115 - b[i] / 0.0002);
		painter->drawLine(72 + i, 115 + 125, 72 + i, 115 + 125 - g[i] / 0.0002);
		painter->drawLine(72 + i, 115 + 2 * 125, 72 + i, 115 + 2 * 125 - r[i] / 0.0002);
	}

}

