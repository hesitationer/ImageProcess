#include "filter.h"

Filter::Filter()
{
}

Filter::~Filter()
{
}

void Filter::lomo(Mat &img, Mat overlay)
{
	/*QVector<int> xRange;
	xRange.push_back(0);
	xRange.push_back(50);
	xRange.push_back(150);
	xRange.push_back(255);
	QVector<float> grad;
	grad.push_back(0.5);
	grad.push_back(2);
	grad.push_back(0.5);
	QVector<float> bias;
	bias.push_back(0);
	bias.push_back(-75);
	bias.push_back(150);
	imageEnhancement.pieceWiseTrans(img, xRange, grad, bias);*/

	float ratio_x = (float)overlay.cols / img.cols;
	float ratio_y = (float)overlay.rows / img.rows;

	for (int i = 0; i < img.cols; i++)
	{
		for (int  j = 0; j < img.rows; j++)
		{
			int A_r = img.at<Vec3b>(j, i)[0];
			int A_g = img.at<Vec3b>(j, i)[1];
			int A_b = img.at<Vec3b>(j, i)[2];
			int B_r = overlay.at<Vec3b>(j * ratio_y, i * ratio_x)[0];
			int B_g = overlay.at<Vec3b>(j * ratio_y, i * ratio_x)[1];
			int B_b = overlay.at<Vec3b>(j * ratio_y, i * ratio_x)[2];
			int C_r, C_g, C_b;
			C_r = B_r <= 128 ? (A_r * B_r) / 128 + ((double)A_r / 255) * ((double)A_r / 255) * (255 - 2 * B_r) :
				A_r * (255 - B_r) / 128 + sqrt((double)A_r / 255) * (2 * B_r - 255);
			C_g = B_g <= 128 ? (A_g * B_g) / 128 + ((double)A_g / 255) * ((double)A_g / 255) * (255 - 2 * B_g) :
				A_g * (255 - B_g) / 128 + sqrt((double)A_g / 255) * (2 * B_g - 255);
			C_b = B_b <= 128 ? (A_b * B_b) / 128 + ((double)A_b / 255) * ((double)A_b / 255) * (255 - 2 * B_b) :
				A_b * (255 - B_b) / 128 + sqrt((double)A_b / 255) * (2 * B_b - 255);

			/*C_r = A_r <= 128 ? (A_r * B_r) / 255 : 255 - (255 - A_r) * (255 - B_r) / 128;
			C_g = A_g <= 128 ? (A_g * B_g) / 255 : 255 - (255 - A_g) * (255 - B_g) / 128;
			C_b = A_b <= 128 ? (A_b * B_b) / 255 : 255 - (255 - A_b) * (255 - B_b) / 128;*/
			img.at<Vec3b>(j, i)[0] = common.checkOverFlow(C_r);
			img.at<Vec3b>(j, i)[1] = common.checkOverFlow(C_g);
			img.at<Vec3b>(j, i)[2] = common.checkOverFlow(C_b);
		}
	}
	imageEnhancement.nonLinearGamaTrans(img, 1.1, 0.9);

}

void Filter::grayscaleRelief(Mat &img)
{
	Mat temp(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));
	for (int i = 0; i < img.cols; i++)
	{
		for (int j = 0; j < img.rows; j++)
		{
			int r, g, b;
			int i_1 = i - 1 < 0 ? img.cols + i - 1 : i - 1;
			int i_2 = i + 1 >= img.cols ? i + 1 - img.cols : i + 1;
			int j_1 = j - 1 < 0 ? img.rows + j - 1 : j - 1;
			int j_2 = j + 1 >= img.rows ? j + 1 - img.rows : j + 1;

			r = img.at<Vec3b>(j_1, i_1)[0] - img.at<Vec3b>(j_2, i_2)[0] + 128;
			g = img.at<Vec3b>(j_1, i_1)[1] - img.at<Vec3b>(j_2, i_2)[1] + 128;
			b = img.at<Vec3b>(j_1, i_1)[2] - img.at<Vec3b>(j_2, i_2)[2] + 128;
			
			temp.at<Vec3b>(j, i)[0] = common.checkOverFlow(r);
			temp.at<Vec3b>(j, i)[1] = common.checkOverFlow(g);
			temp.at<Vec3b>(j, i)[2] = common.checkOverFlow(b);
		}
	}
	img = temp;
}

void Filter::pencilDrawing(Mat &img)
{
	Mat gray0;
	cvtColor(img, gray0, CV_RGB2GRAY);

}