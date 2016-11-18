#include "hsi.h"
using namespace std;
Hsi::Hsi()
{
}

Hsi::~Hsi()
{
}


void Hsi::changeLight(Mat &img, int value)
{
	Mat hsi(img.rows, img.cols, CV_32FC3);
	bgr2hsi(img, hsi);
	for (int ii = 0; ii < hsi.cols; ii++)
	{
		for (int j = 0; j < hsi.rows; j++)
		{
			float i = hsi.at<Vec3f>(Point(ii, j))[2];
			if (i + (float)value < 0)
			{
				i = 0;
			}
			else if (i + (float)value  > 255)
			{
				i = 255;
			}
			else
			{
				i = i + (float)value;
			}
			hsi.at<Vec3f>(Point(ii, j))[2] = i;
		}
	}
	hsi2bgr(hsi, img);
}

void Hsi::changeSaturation(Mat &img, int value)
{
	Mat hsi(img.rows, img.cols, CV_32FC3);
	bgr2hsi(img, hsi);
	for (int i = 0; i < hsi.cols; i++)
	{
		for (int j = 0; j < hsi.rows; j++)
		{
			float s = hsi.at<Vec3f>(Point(i, j))[1];
			if (s + (float)value < 0)
			{
				s = 0;
			}
			else if (s + (float)value > 100)
			{
				s = 100;
			}
			else
			{
				s = s + (float)value;
			}
			hsi.at<Vec3f>(Point(i, j))[1] = s;
		}
	}
	hsi2bgr(hsi, img);
}

void Hsi::changeTone(Mat &img, int value)
{
	Mat hsi(img.rows, img.cols, CV_32FC3);
	bgr2hsi(img, hsi);
	for (int i = 0; i < hsi.cols; i++)
	{
		for (int j = 0; j < hsi.rows; j++)
		{
			float h = hsi.at<Vec3f>(Point(i, j))[0];
			if (h + (float)value < 0)
			{
				h = 0;
			}
			else if (h + (float)value > 360)
			{
				h = 360;
			}
			else
			{
				h = h + (float)value;
			}
			hsi.at<Vec3f>(Point(i, j))[0] = h;
		}
	}
	hsi2bgr(hsi, img);
}

void Hsi::bgr2hsi(Mat &bgr, Mat &hsi)
{
	for (int ii = 0; ii < bgr.cols; ii++)
	{
		for (int j = 0; j < bgr.rows; j++)
		{
			float b = bgr.at<Vec3b>(Point(ii, j))[0];
			float g = bgr.at<Vec3b>(Point(ii, j))[1];
			float r = bgr.at<Vec3b>(Point(ii, j))[2];
			float i = (b + g + r) / 3;
			float s = 1 - 3 * min(min(b, g), r) / (b + g + r);
			float h;

			h = 0.5 * ((r - g) + (r - b)) / sqrt(((r - g)*(r - g)) + ((r - b)*(g - b)));
			h = acos(h);
			
			hsi.at<Vec3f>(Point(ii, j))[0] = (h * 180) / CV_PI;
			hsi.at<Vec3f>(Point(ii, j))[1] = s * 100;
			hsi.at<Vec3f>(Point(ii, j))[2] = i;

		}
	}
}

void Hsi::hsi2bgr(Mat &hsi, Mat &bgr)
{
	for (int ii = 0; ii < bgr.cols; ii++)
	{
		for (int j = 0; j < bgr.rows; j++)
		{
			float h = hsi.at<Vec3f>(Point(ii, j))[0];
			float s = hsi.at<Vec3f>(Point(ii, j))[1] / 100.0;
			float i = hsi.at<Vec3f>(Point(ii, j))[2];
			int b, g, r;

			if (h >=0  && h <= 120)
			{
				b = i * (1 - s);
				r = i * (1 + s * cos(h * CV_PI / 180) / cos((60 - h) * CV_PI / 180));
				g = 3 * i - (b + r);
				g = g > 255 ? 255 : g;
				r = r > 255 ? 255 : r;
			}
			else if (h > 120 && h <= 240)
			{
				r = i * (1 - s);
				g = i * (1 + s * cos((h  - 120) * CV_PI / 180 ) / cos((180 - h) * CV_PI / 180));
				b = 3 * i - (r + g);
				g = g > 255 ? 255 : g;
				b = b > 255 ? 255 : b;
			}
			else
			{
				g = i * (1 - s);
				b = i * (1 + s * cos((h - 240) * CV_PI / 180 ) / cos((300 - h) * CV_PI / 180));
				r = 3 * i - (r + g);
				b = b > 255 ? 255 : b;
				r = r > 255 ? 255 : r;
			}

			bgr.at<Vec3b>(Point(ii, j))[0] = b;
			bgr.at<Vec3b>(Point(ii, j))[1] = g;
			bgr.at<Vec3b>(Point(ii, j))[2] = r;
		}
	}
}
