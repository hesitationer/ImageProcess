#include "cut_image.h"
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;
CutImage::CutImage()
{
}

CutImage::~CutImage()
{
}

void CutImage::cutRect(Mat &img, int x, int y, int w, int h)
{
	Mat temp(w, h, img.type());
	for (int i = 0; i < temp.cols; i++)
	{
		for (int j = 0; j < temp.rows; j++)
		{
			if (x + i >= img.cols || y + j >= img.rows)
			{
				continue;
			}
			temp.at<Vec3b>(Point(i, j)) = img.at<Vec3b>(Point(x + i, y + j));
		}

	}
	img = temp;
}

void CutImage::cutRound(Mat &img, QPoint center, int r)
{
	Mat temp(r * 2, r * 2, img.type(), cv::Scalar(255, 255, 255));
	for (int i = 0; i < r * 2; i++)
	{
		for (int j = 0; j < r * 2; j++)
		{
			if (center.x() - r + i >= img.cols || center.y() - r + j >= img.rows || center.x() - r + i < 0 || center.y() - r + j < 0)
			{
				continue;
			}
			double dis = sqrt((i - r) * (i - r) + (j - r) * (j - r));
			if (dis > (double)r)
			{
				continue;
			}
			temp.at<Vec3b>(Point(i, j)) = img.at<Vec3b>(Point(center.x() - r + i, center.y() - r + j));
		}
	}
	img = temp;
}

void CutImage::cutPolygon(Mat &img, QVector<QPoint> points)
{
	int min_x, min_y, max_x, max_y;
	min_x = max_x = points.at(0).x();
	min_y = max_y = points.at(0).y();
	for (int i = 0; i < points.size(); i++)
	{
		if (min_x > points.at(i).x())
		{
			min_x = points.at(i).x();
		}

		if (max_x < points.at(i).x())
		{
			max_x = points.at(i).x();
		}

		if (min_y > points.at(i).y())
		{
			min_y = points.at(i).y();
		}

		if (max_y < points.at(i).y())
		{
			max_y = points.at(i).y();
		}
	}
	Mat temp(max_y - min_y + 1, max_x - min_x + 1, img.type(), cv::Scalar(255, 255, 255));
	QVector<int> xs;

	for (int j = 0; j < temp.rows; j++)
	{
		int y = j + min_y;
		for (int k = 0; k < points.size(); k++)
		{
			int k_min_y;
			int k_max_y;
			int k_min_x;
			int k_max_x;
			int kk;
			if (k == points.size() - 1)
			{
				kk = 0;
			}
			else
			{
				kk = k + 1;
			}
			if (points.at(k).y() < points.at(kk).y())
			{
				k_min_y = points.at(k).y();
				k_max_y = points.at(kk).y();
			}
			else
			{
				k_min_y = points.at(kk).y();
				k_max_y = points.at(k).y();
			}

			if (points.at(k).x() < points.at(kk).x())
			{
				k_min_x = points.at(k).x();
				k_max_x = points.at(kk).x();
			}
			else
			{
				k_min_x = points.at(kk).x();
				k_max_x = points.at(k).x();
			}

			if (k_min_y < y && k_max_y >= y)
			{
				xs.push_back(points.at(k).x() + (int)round((double)(points.at(kk).x() - points.at(k).x()) * (double)(y - points.at(k).y()) / (double)(points.at(kk).y() - points.at(k).y())));
			}
		}

		sort(xs.begin(), xs.end());

		for (int m = 0; m < xs.size() - 1; m++)
		{
			if ((m + 1) % 2 == 1 && ( xs.size() - m - 1) % 2 == 1)
			{
				for (int i = xs.at(m); i <= xs.at(m+1); i++)
				{
					if (i - min_x >= temp.cols || i >= img.cols)
					{
						continue;
					}
					temp.at<Vec3b>(Point(i - min_x, j)) = img.at<Vec3b>(Point(i, y));
				}
			}
			else
			{
				continue;
			}
		}
		xs.clear();
	}
	img = temp;
}