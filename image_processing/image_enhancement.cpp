#include "image_enhancement.h"
ImageEnhancement::ImageEnhancement()
{
}

ImageEnhancement::~ImageEnhancement()
{
}

void ImageEnhancement::histEquTrans(Mat &img)
{
	float b[256];
	float g[256];
	float r[256];
	int i, j;
	for ( i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
	}
	getHistOfImg(img, b, g, r, 256);
	getEqu(b);
	getEqu(g);
	getEqu(r);
	for (int p = 0; p < 256; p++)
	{
		b[p] = b[p] * 255 + 0.5;
		g[p] = g[p] * 255 + 0.5;
		r[p] = r[p] * 255 + 0.5;
	}
	for (i = 0; i < img.cols; i++)
	{
		for (j = 0; j < img.rows; j++)
		{
			int k = img.at<Vec3b>(Point(i, j))[0];
			img.at<Vec3b>(Point(i, j))[0] = int(b[k]);
			k = img.at<Vec3b>(Point(i, j))[1];
			img.at<Vec3b>(Point(i, j))[1] = int(g[k]);
			k = img.at<Vec3b>(Point(i, j))[2];
			img.at<Vec3b>(Point(i, j))[2] = int(r[k]);
		}
	}
}

void ImageEnhancement::histSpecTrans(Mat &img, float b_spec[], float g_spec[], float r_spec[])
{
	float b[256];
	float g[256];
	float r[256];
	int b_b[256], g_g[256], r_r[256];

	int i, j;
	for (i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
		b_b[i] = 0;
		g_g[i] = 0;
		r_r[i] = 0;
	}
	getHistOfImg(img, b, g, r, 256);
	getEqu(b);
	getEqu(g);
	getEqu(r);

	int b_flag = 0;
	int g_flag = 0;
	int r_flag = 0;
	for ( i = 0; i < 256; i++)
	{
		for (j = b_flag; j < 255; j++)
		{
			if (abs(b[i] - b_spec[j]) < abs(b[i] - b_spec[j+1]) && b[i] >= b_spec[j])
			{
				b_b[i] = j;
				b_flag = j;
				break;
			}
			if (j == 254)
			{
				b_b[i] = 255;
			}
		}
		for (j = g_flag; j < 255; j++)
		{
			if (abs(g[i] - g_spec[j]) < abs(g[i] - g_spec[j + 1]) && g[i] >= g_spec[j])
			{
				g_g[i] = j;
				g_flag = j;
				break;
			}
			if (j == 254)
			{
				g_g[i] = 255;
			}
		}

		for (j = r_flag; j < 255; j++)
		{
			if (abs(r[i] - r_spec[j]) < abs(r[i] - r_spec[j + 1]) && r[i] >= r_spec[j])
			{
				r_r[i] = j;
				r_flag = j;
				break;
			}
			if (j == 254)
			{
				r_r[i] = 254;
			}
		}
	}

	for (i = 0; i < img.cols; i++)
	{
		for (j = 0; j < img.rows; j++)
		{
			img.at<Vec3b>(Point(i, j))[0] = b_b[img.at<Vec3b>(Point(i, j))[0]];
			img.at<Vec3b>(Point(i, j))[1] = g_g[img.at<Vec3b>(Point(i, j))[1]];
			img.at<Vec3b>(Point(i, j))[2] = r_r[img.at<Vec3b>(Point(i, j))[2]];
		}
	}
}

void ImageEnhancement::histSpecGMLTrans(Mat &img, float b_spec[], float g_spec[], float r_spec[])
{
	float b[256];
	float g[256];
	float r[256];
	int b_b[256], g_g[256], r_r[256];

	int i, j;
	for (i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
		b_b[i] = 0;
		g_g[i] = 0;
		r_r[i] = 0;
	}
	getHistOfImg(img, b, g, r, 256);
	getEqu(b);
	getEqu(g);
	getEqu(r);

	int b_flag = 0;
	int g_flag = 0;
	int r_flag = 0;
	for (i = 0; i < 256; i++)
	{
		for (j = b_flag; j < 255; j++)
		{
			if (abs(b_spec[i] - b[j]) < abs(b_spec[i] - b[j + 1]) && b_spec[i] >= b[j])
			{
				b_b[j] = i;
				b_flag = j;
				break;
			}
			if (j == 254)
			{
				b_b[j] = 255;
			}
		}
		for (j = g_flag; j < 255; j++)
		{
			if (abs(g_spec[i] - g[j]) < abs(g_spec[i] - g[j + 1]) && g_spec[i] >= g[j])
			{
				g_g[j] = i;
				g_flag = j;
				break;
			}
			if (j == 254)
			{
				g_g[j] = 255;
			}
		}

		for (j = r_flag; j < 255; j++)
		{
			if (abs(r_spec[i] - r[j]) < abs(r_spec[i] - r[j + 1]) && r_spec[i] >= r[j])
			{
				r_r[j] = i;
				r_flag = j;
				break;
			}
			if (j == 254)
			{
				r_r[j] = 255;
			}
		}
	}

	for  (i = 254; i > 0; i--)
	{
		if (b_b[i] == 0)
		{
			b_b[i] = b_b[i + 1];
		}
		if (g_g[i] == 0)
		{
			g_g[i] = g_g[i + 1];
		}

		if (r_r[i] == 0)
		{
			r_r[i] = r_r[i + 1];
		}
	}

	for (i = 0; i < img.cols; i++)
	{
		for (j = 0; j < img.rows; j++)
		{
			img.at<Vec3b>(Point(i, j))[0] = b_b[img.at<Vec3b>(Point(i, j))[0]];
			img.at<Vec3b>(Point(i, j))[1] = g_g[img.at<Vec3b>(Point(i, j))[1]];
			img.at<Vec3b>(Point(i, j))[2] = r_r[img.at<Vec3b>(Point(i, j))[2]];
		}
	}
}

void ImageEnhancement::linearTrans(Mat &img, float grid, float bias)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int b = img.at<Vec3b>(Point(i, j))[0];
			int g = img.at<Vec3b>(Point(i, j))[1];
			int r = img.at<Vec3b>(Point(i, j))[2];
			b = (int)(grid * b + bias);
			b = common.checkOverFlow(b);
			g = (int)(grid * g + bias);
			g = common.checkOverFlow(g);
			r = (int)(grid * r + bias);
			r = common.checkOverFlow(r);
			img.at<Vec3b>(Point(i, j))[0] = b;
			img.at<Vec3b>(Point(i, j))[1] = g;
			img.at<Vec3b>(Point(i, j))[2] = r;
		}
	}
}

//
int ImageEnhancement::exp(int r, float a, float b, float c)
{
	r = (int)qPow(b, c * (r - a)) - 1;
	return common.checkOverFlow(r);
}
void ImageEnhancement::nonLinearExpTrans(Mat &img, float a, float b, float c)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int bb = img.at<Vec3b>(Point(i, j))[0];
			int g = img.at<Vec3b>(Point(i, j))[1];
			int r = img.at<Vec3b>(Point(i, j))[2];
			bb = exp(bb, a, b, c);
			g = exp(g, a, b, c);
			r = exp(r, a, b, c);
			img.at<Vec3b>(Point(i, j))[0] = bb;
			img.at<Vec3b>(Point(i, j))[1] = g;
			img.at<Vec3b>(Point(i, j))[2] = r;
		}
	}
}

void ImageEnhancement::nonLinearGamaTrans(Mat &img, float gama, float c)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int bb = img.at<Vec3b>(Point(i, j))[0];
			int g = img.at<Vec3b>(Point(i, j))[1];
			int r = img.at<Vec3b>(Point(i, j))[2];
			bb = c * qPow(bb, gama);
			g = c * qPow(g, gama);
			r = c * qPow(r, gama);
			bb = common.checkOverFlow(bb);
			g = common.checkOverFlow(g);
			r = common.checkOverFlow(r);
			img.at<Vec3b>(Point(i, j))[0] = bb;
			img.at<Vec3b>(Point(i, j))[1] = g;
			img.at<Vec3b>(Point(i, j))[2] = r;
		}
	}
}

void ImageEnhancement::nonLinearLogTrans(Mat &img, float c)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int bb = img.at<Vec3b>(Point(i, j))[0];
			int g = img.at<Vec3b>(Point(i, j))[1];
			int r = img.at<Vec3b>(Point(i, j))[2];
			bb = c * qLn(bb + 1);
			bb = common.checkOverFlow(bb);
			g = c * qLn(g + 1);
			g = common.checkOverFlow(g);
			r = c * qLn(r + 1);
			r = common.checkOverFlow(r);
			img.at<Vec3b>(Point(i, j))[0] = bb;
			img.at<Vec3b>(Point(i, j))[1] = g;
			img.at<Vec3b>(Point(i, j))[2] = r;
		}
	}
}

void ImageEnhancement::pieceWiseTrans(Mat &img, QVector<int> xRange, QVector<float> grad, QVector<float> bias)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int b = piecewiseTransSplit(img.at<Vec3b>(Point(i, j))[0], xRange, grad, bias);
			int g = piecewiseTransSplit(img.at<Vec3b>(Point(i, j))[1], xRange, grad, bias);
			int r = piecewiseTransSplit(img.at<Vec3b>(Point(i, j))[2], xRange, grad, bias);
			img.at<Vec3b>(Point(i, j))[0] = b;
			img.at<Vec3b>(Point(i, j))[1] = g;
			img.at<Vec3b>(Point(i, j))[2] = r;
			
		}
	}
}


int ImageEnhancement::piecewiseTransSplit(int r, QVector<int> xRange, QVector<float> grad, QVector<float> bias)
{
	int index;
	for (int i = 0; i < xRange.size() - 1; i++)
	{
		if (r >= xRange.at(i) && r <= xRange.at(i+1))
		{
			index = i;
			break;
		}
	}

	r = (int)(grad.at(index) * r + bias.at(index));
	return common.checkOverFlow(r);
}

void ImageEnhancement::getHistOfImg(Mat img, float b[], float g[], float r[], int L)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			b[img.at<Vec3b>(Point(i, j))[0]] += 1.0;
			g[img.at<Vec3b>(Point(i, j))[1]] += 1.0;
			r[img.at<Vec3b>(Point(i, j))[2]] += 1.0;
		}
	}

	int size = img.rows * img.cols;
	for (int k = 0; k < L; k++)
	{
		b[k] /= size;
		g[k] /= size;
		r[k] /= size;
	}
}

void ImageEnhancement::getEqu(float s[])
{
	for (int i = 1; i < 256; i++)
	{
		s[i] = s[i - 1] + s[i];
	}
}
