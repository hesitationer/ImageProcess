#include "image_label.h"
#include "main_window.h"
MyImageLabel::MyImageLabel()
{
}

MyImageLabel::MyImageLabel(const QString &str, QWidget *parent)
	:QLabel(str, parent, Qt::WindowFlags())
{
}

MyImageLabel::~MyImageLabel()
{
}

void MyImageLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && scribbling == true)
	{
		if (event->pos().x() >= width || event->pos().y() >= height)
		{
			return;
		}
		if (draw_flag == 3)
		{
			points.append(event->pos());
			//drawPolygon(points);
			update();
			return;
		}
		startPoint = event->pos();
		move = true;
	}
	else
	{
		return;
	}
}

void MyImageLabel::mouseMoveEvent(QMouseEvent *event)
{
	if (draw_flag == 3)
	{
		return;
	}
	if ((event->buttons() & Qt::LeftButton) && scribbling && move)
	{
		//drawRect(startPoint, event->pos());
		endPoint = event->pos();
		update();
	}
}

void MyImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
	if (draw_flag == 3)
	{
		return;
	}

	if ((event->button() == Qt::LeftButton) && scribbling && move)
	{
		endPoint = event->pos();
		update();
		move = false;
		setCursor(Qt::ArrowCursor);
		if (QMessageBox::question(this, tr("confirm"), tr("Are you true to cut the image?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
		{
			if (draw_flag == 1)
			{
				endPoint.setX(endPoint.x() >= width ? width - 1 : endPoint.x());
				endPoint.setY(endPoint.y() >= height ? height - 1 : endPoint.y());
				int w = endPoint.x() > startPoint.x() ? endPoint.x() - startPoint.x() : startPoint.x() - endPoint.x();
				int h = endPoint.y() > startPoint.y() ? endPoint.y() - startPoint.y() : startPoint.y() - endPoint.y();

				int center_x = (startPoint.x() + endPoint.x()) / 2;
				int center_y = (startPoint.y() + endPoint.y()) / 2;
				window->cutRect(center_x - w / 2, center_y - h / 2, h, w);
			}
			else if (draw_flag == 2)
			{
				endPoint.setX(endPoint.x() >= width ? width - 1 : endPoint.x());
				endPoint.setY(endPoint.y() >= height ? height - 1 : endPoint.y());
				int r = (int)(sqrt((startPoint.x() - endPoint.x()) * (startPoint.x() - endPoint.x()) + (startPoint.y() - endPoint.y()) * (startPoint.y() - endPoint.y())) / 2);
				QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);
				window->cutRound(center, r);
			}
			
		}
		else
		{
			draw_flag = 0;
		}
		scribbling = false;
	}
}


void MyImageLabel::drawRect(QPoint start, QPoint end)
{
	painter = new QPainter(this);
	painter->setPen(Qt::DashLine);
	painter->setBrush(Qt::NoBrush);
	painter->begin(this);
	end.setX(end.x() >= width ? width - 1 : end.x());
	end.setY(end.y() >= height ? height - 1 : end.y());
	int w = end.x() > start.x() ? end.x() - start.x() : start.x() - end.x();
	int h = end.y() > start.y() ? end.y() - start.y() : start.y() - end.y();
	painter->drawRect(start.x(), start.y(), w, h);
	painter->end();
	//update();
}

void MyImageLabel::drawRound(QPoint start, QPoint end)
{
	painter = new QPainter(this);
	painter->setPen(Qt::DashLine);
	painter->setBrush(Qt::NoBrush);
	painter->begin(this);
	end.setX(end.x() >= width ? width - 1 : end.x());
	end.setY(end.y() >= height ? height - 1 : end.y());
	int r = (int)(sqrt((startPoint.x() - endPoint.x()) * (startPoint.x() - endPoint.x()) + (startPoint.y() - endPoint.y()) * (startPoint.y() - endPoint.y())) / 2);
	QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

	painter->drawEllipse(center, r, r);
	painter->end();
}

void MyImageLabel::drawPolygon(QVector<QPoint> points, int flag)
{
	if (points.size() == 1)
	{
		return;
	}
	painter = new QPainter(this);
	painter->setPen(Qt::DashLine);
	painter->setBrush(Qt::NoBrush);
	painter->begin(this);
	for (int i = 0; i < points.size() - 1; i++)
	{
		painter->drawLine(points.at(i), points.at(i + 1));
	}

	if (flag == 1)
	{
		painter->drawLine(points.at(0), points.at(points.size() - 1));
	}

	painter->end();
}

void MyImageLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	QPainter painter(this);
	if (draw_flag == 0)
	{
		return;
	}
	else if (draw_flag == 1)
	{
		drawRect(startPoint, endPoint);
	}
	else if (draw_flag == 2)
	{
		drawRound(startPoint, endPoint);
	}
	else if (draw_flag == 3)
	{
		drawPolygon(points, polygon_flag);
	}
}