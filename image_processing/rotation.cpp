#include "rotation.h"
Rotation::Rotation()
{
}

Rotation::~Rotation()
{
}

void Rotation::rotation_image(Mat &img, bool left, int degree)
{
	double angle = degree  * CV_PI / 180; // 弧度   
	double a = sin(angle), b = cos(angle);
	int width = img.cols;
	int height = img.rows;
	int width_rotate = int(height * fabs(a) + width * fabs(b));
	int height_rotate = int(width * fabs(a) + height * fabs(b));
	Mat temp(width_rotate, height_rotate, img.type(), cv::Scalar(255,255,255));

	width_rotate = temp.cols;
	height_rotate = temp.rows;


	for (int row = 0; row < height_rotate; row++)
	{
		for (int col = 0; col < width_rotate; col++)
		{
			//先求得旋转前相对于中心点的坐标
			int x = col - width_rotate / 2;
			int y = height_rotate / 2 - row;

			//计算x,y旋转之后相对于中心点的坐标
			int x_rotate = (int)round(x * b - y * a);
			int y_rotate = (int)round(x * a + y * b);

			//计算旋转之后基于左上角的坐标

			int col_rotate = x_rotate + width / 2;
			int row_rotate = height / 2 - y_rotate;

			if (col_rotate < 0 || col_rotate >= width || row_rotate < 0 || row_rotate >= height)
			{
				continue;
			}
			
			temp.at<Vec3b>(Point(col, row)) = img.at<Vec3b>(Point(col_rotate, row_rotate));

		}
	}
	img = temp;

}

void Rotation::flipHorizontal(Mat &img)
{
	Mat temp = img.clone();
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img.at<Vec3b>(Point(j, i)) = temp.at<Vec3b>(Point((temp.cols - 1 - j), i));
		}
	}
}

void Rotation::flipVertical(Mat &img)
{
	Mat temp = img.clone();
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			img.at<Vec3b>(Point(i, j)) = temp.at<Vec3b>(Point(i, img.size().height - 1 - j));
		}
	}
}

void Rotation::rotate90(Mat &img)
{
	Mat temp(img.cols, img.rows, img.type());
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			temp.at<Vec3b>(Point(temp.cols - 1 - i, j)) = img.at<Vec3b>(Point(j, i));
		}
	}
	img = temp;
}

void Rotation::rotate180(Mat &img)
{
	Mat temp = img.clone();
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			img.at<Vec3b>(Point(i, j)) = temp.at<Vec3b>(Point(img.size().width - 1 - i, img.size().height - 1 - j));
		}
	}
}
double Rotation::round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}