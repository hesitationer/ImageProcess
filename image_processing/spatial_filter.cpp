#include "spatial_filter.h"

SpatialFilter::SpatialFilter()
{
}

SpatialFilter::~SpatialFilter()
{
}

void SpatialFilter::medianFilter(Mat &img, int template_size, bool **template_shape)
{
	Mat temp(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			Vector<int> med_b, med_g, med_r;
			for (int k = i - template_size / 2; k <= i + template_size / 2; k++)
			{
				for (int l = j - template_size / 2; l <= j + template_size / 2; l++)
				{

					if (template_shape[k - i + template_size / 2][l - j + template_size / 2])
					{
						if (k < 0 || l < 0 || k >= img.cols || l >= img.rows)
						{
							med_b.push_back(0);
							med_g.push_back(0);
							med_r.push_back(0);
						}
						else
						{
							med_b.push_back(img.at<Vec3b>(l, k)[0]);
							med_g.push_back(img.at<Vec3b>(l, k)[1]);
							med_r.push_back(img.at<Vec3b>(l, k)[2]);
						}
					}
				}
			}
			sort(med_b.begin(), med_b.end());
			sort(med_g.begin(), med_g.end());
			sort(med_r.begin(), med_r.end());

			int temp_length = med_b.size();
			int b, g, r;
			if (med_b.size() % 2 == 1)
			{
				b = med_b[temp_length / 2 + 1];
				g = med_g[temp_length / 2 + 1];
				r = med_r[temp_length / 2 + 1];
			}
			else
			{
				b = (med_b[temp_length / 2] + med_b[temp_length / 2 + 1]) / 2;
				g = (med_g[temp_length / 2] + med_g[temp_length / 2 + 1]) / 2;
				r = (med_r[temp_length / 2] + med_r[temp_length / 2 + 1]) / 2;

			}

			temp.at<Vec3b>(j, i)[0] = b;
			temp.at<Vec3b>(j, i)[1] = g;
			temp.at<Vec3b>(j, i)[2] = r;
	
		}
	}
	img = temp;
}

void SpatialFilter::gaussianBlur(Mat &img, float sigma, int template_size)
{
	float **template_parm;
	template_parm = new float *[template_size];
	float sigma2 = 2 * sigma * sigma;
	float sigmaPi = sigma2 * CV_PI;
	float sum = 0.0;
	int i, j, k, l;
	for ( i = 0; i < template_size; i++)
	{
		template_parm[i] = new float[template_size];
		for ( j = 0; j < template_size; j++)
		{
			float parm = exp(-(float)((i - template_size / 2) * (i - template_size / 2) + (j - template_size / 2) * (j - template_size / 2)) / sigma2) / sigmaPi;
			template_parm[i][j] = parm;
			sum += parm;
		}
	}

	for ( i = 0; i < template_size; i++)
	{
		for (j = 0; j < template_size; j++)
		{
			template_parm[i][j] /= sum;
		}
	}

	Mat temp(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));

	for ( i = 0; i < img.cols; i++)
	{
		for ( j = 0; j < img.rows; j++)
		{
			float b = 0.0, g = 0.0 , r = 0.0;
			for ( k = i - template_size / 2; k <= i + template_size / 2; k++)
			{
				for ( l = j - template_size /  2; l <= j + template_size /  2; l++)
				{
					int kk = k < 0 ? img.cols + k : k;
					kk = kk >= img.cols ? kk - img.cols : kk;
					int ll = l < 0 ? img.rows + l : l;
					ll = ll >= img.rows ? ll - img.rows : ll;

					b += img.at<Vec3b>(ll, kk)[0] * template_parm[k - i + template_size / 2][l - j + template_size / 2];
					g += img.at<Vec3b>(ll, kk)[1] * template_parm[k - i + template_size / 2][l - j + template_size / 2];
					r += img.at<Vec3b>(ll, kk)[2] * template_parm[k - i + template_size / 2][l - j + template_size / 2];

				}
			}
			temp.at<Vec3b>(j, i)[0] = (int)b;
			temp.at<Vec3b>(j, i)[1] = (int)g;
			temp.at<Vec3b>(j, i)[2] = (int)r;

		}
	}

	img = temp;

}

void SpatialFilter::sharpenLaplace(Mat &img, int threshold, int incremental)
{
	int temp1[3][3] = { 0, 1, 0, 1, -4, 1, 0, 1, 0 };
	int temp2[3][3] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
	int temp3[3][3] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };
	int temp4[3][3] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };
	Mat temp(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			if (i - 1 < 0 || j - 1 < 0 || j + 1 >= img.rows || i + 1 >= img.cols)
			{
				temp.at<Vec3b>(j, i) = img.at<Vec3b>(j, i);
			}
			else
			{
				int sum1_b = 0, sum2_b = 0, sum3_b = 0, sum4_b = 0,
					sum1_g = 0, sum2_g = 0, sum3_g = 0, sum4_g = 0,
					sum1_r = 0, sum2_r = 0, sum3_r = 0, sum4_r = 0;
				for (int k = i - 1; k <= i + 1; k++)
				{
					for (int l = j - 1; l <= j + 1; l++)
					{
						sum1_b += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum2_b += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum3_b += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum4_b += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum1_g += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum2_g += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum3_g += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum4_g += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum1_r += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
						sum2_r += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
						sum3_r += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
						sum4_r += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
					}
				}

				if (abs(sum1_b) / 8 + abs(sum2_b) / 8  + abs(sum3_b) / 16 + abs(sum4_b) / 16 > threshold * 4)
				{
					temp.at<Vec3b>(j, i)[0] = common.checkOverFlow(img.at<Vec3b>(j, i)[0] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[0] = img.at<Vec3b>(j, i)[0];
				}
				if (abs(sum1_g) / 8 + abs(sum2_g) / 8 + abs(sum3_g) / 16 + abs(sum4_g) / 16 > threshold * 4)
				{
					temp.at<Vec3b>(j, i)[1] = common.checkOverFlow(img.at<Vec3b>(j, i)[1] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[1] = img.at<Vec3b>(j, i)[1];
				}
				if (abs(sum1_r) / 8 + abs(sum2_r) / 8 + abs(sum3_r) / 16 + abs(sum4_r) / 16 > threshold * 4)
				{
					temp.at<Vec3b>(j, i)[2] = common.checkOverFlow(img.at<Vec3b>(j, i)[2] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[2] = img.at<Vec3b>(j, i)[2];
				}
			}
		}
	}

	img = temp;
}

void SpatialFilter::sharpenPrewitt(Mat &img, int threshold, int incremental)
{
	int temp1[3][3] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	int temp2[3][3] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	Mat temp(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			if (i - 1 < 0 || j - 1 < 0 || j + 1 >= img.rows || i+1 >= img.cols)
			{
				temp.at<Vec3b>(j, i) = img.at<Vec3b>(j, i);
			}
			else
			{
				int sum1_b = 0, sum2_b = 0, sum1_g = 0, sum2_g = 0, sum1_r = 0, sum2_r = 0;
				for (int k = i - 1; k <= i+1 ; k++)
				{
					for (int l = j - 1; l <= j + 1; l++)
					{
						sum1_b += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum2_b += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum1_g += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum2_g += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum1_r += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
						sum2_r += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
					}
				}

				if (abs(sum1_b) / 6 + abs(sum2_b) / 6 > threshold * 2)
				{
					temp.at<Vec3b>(j, i)[0] = common.checkOverFlow(img.at<Vec3b>(j, i)[0] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[0] = img.at<Vec3b>(j, i)[0];
				}
				if (abs(sum1_g) / 6 + abs(sum2_g) / 6 > threshold * 2)
				{
					temp.at<Vec3b>(j, i)[1] = common.checkOverFlow(img.at<Vec3b>(j, i)[1] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[1] = img.at<Vec3b>(j, i)[1];
				}
				if (abs(sum1_r) / 6 + abs(sum2_r) / 6 > threshold * 2)
				{
					temp.at<Vec3b>(j, i)[2] = common.checkOverFlow(img.at<Vec3b>(j, i)[2] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[2] = img.at<Vec3b>(j, i)[2];
				}
			}
		}
	}

	img = temp;
}

void SpatialFilter::sharpenSobel(Mat &img, int threshold, int incremental)
{
	int temp1[3][3] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	int temp2[3][3] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	Mat temp(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			if (i - 1 < 0 || j - 1 < 0 || j + 1 >= img.rows || i + 1 >= img.cols)
			{
				temp.at<Vec3b>(j, i) = img.at<Vec3b>(j, i);
			}
			else
			{
				int sum1_b = 0, sum2_b = 0, sum1_g = 0, sum2_g = 0, sum1_r = 0, sum2_r = 0;
				for (int k = i - 1; k <= i + 1; k++)
				{
					for (int l = j - 1; l <= j + 1; l++)
					{
						sum1_b += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum2_b += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[0];
						sum1_g += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum2_g += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[1];
						sum1_r += temp1[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
						sum2_r += temp2[k - i + 1][l - j + 1] * img.at<Vec3b>(l, k)[2];
					}
				}

				if (abs(sum1_b) / 8 + abs(sum2_b) / 8 > threshold * 2)
				{
					temp.at<Vec3b>(j, i)[0] = common.checkOverFlow(img.at<Vec3b>(j, i)[0] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[0] = img.at<Vec3b>(j, i)[0];
				}
				if (abs(sum1_g) / 8 + abs(sum2_g) / 8 > threshold * 2)
				{
					temp.at<Vec3b>(j, i)[1] = common.checkOverFlow(img.at<Vec3b>(j, i)[1] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[1] = img.at<Vec3b>(j, i)[1];
				}
				if (abs(sum1_r) / 8 + abs(sum2_r) / 8 > threshold * 2)
				{
					temp.at<Vec3b>(j, i)[2] = common.checkOverFlow(img.at<Vec3b>(j, i)[2] + incremental);
				}
				else
				{
					temp.at<Vec3b>(j, i)[2] = img.at<Vec3b>(j, i)[2];
				}
			}
		}
	}

	img = temp;
}

void SpatialFilter::sharpenRoberts(Mat &img, int threshold, int incremental)
{
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int z5_b, z6_b, z8_b, z9_b, z5_g, z6_g, z8_g, z9_g, z5_r, z6_r, z8_r, z9_r;
			z5_b = img.at<Vec3b>(j, i)[0];
			z5_g = img.at<Vec3b>(j, i)[1];
			z5_r = img.at<Vec3b>(j, i)[2];

			if (i + 1 >= img.cols)
			{
				z6_b = 0;
				z6_g = 0;
				z6_r = 0;
			}
			else
			{
				z6_b = img.at<Vec3b>(j, i+1)[0];
				z6_g = img.at<Vec3b>(j, i+1)[1];
				z6_r = img.at<Vec3b>(j, i+1)[2];
			}

			if (j + 1 >= img.rows)
			{
				z8_b = 0;
				z8_g = 0;
				z8_r = 0;
			}
			else
			{
				z8_b = img.at<Vec3b>(j+1, i)[0];
				z8_g = img.at<Vec3b>(j+1, i)[1];
				z8_r = img.at<Vec3b>(j+1, i)[2];
			}

			if (i+1 >= img.cols || j+1 >= img.rows)
			{
				z9_b = 0;
				z9_g = 0;
				z9_r = 0;
			}
			else
			{
				z9_b = img.at<Vec3b>(j + 1, i + 1)[0];
				z9_g = img.at<Vec3b>(j + 1, i + 1)[1];
				z9_r = img.at<Vec3b>(j + 1, i + 1)[2];
			}

			if((int)fabs((double)z5_b - z9_b) + (int)fabs((double)z6_b - z8_b) > threshold * 4)
				img.at<Vec3b>(j, i)[0] = common.checkOverFlow(img.at<Vec3b>(j, i)[0] + incremental);
			if((int)fabs((double)z5_g - z9_g) + (int)fabs((double)z6_g - z8_g) > threshold * 4)
				img.at<Vec3b>(j, i)[1] = common.checkOverFlow(img.at<Vec3b>(j, i)[1] + incremental);
			if((int)fabs((double)z5_r - z9_r) + (int)fabs((double)z6_r - z8_r) > threshold * 4)
				img.at<Vec3b>(j, i)[2] = common.checkOverFlow(img.at<Vec3b>(j, i)[2] + incremental);
		}
	}
}