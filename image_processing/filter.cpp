#include "filter.h"

Filter::Filter()
{
}

Filter::~Filter()
{
}

void Filter::lomo(Mat &img, Mat overlay)
{

	float ratio_x = (float)overlay.cols / img.cols;
	float ratio_y = (float)overlay.rows / img.rows;

	for (int i = 0; i < img.cols; i++)
	{
		for (int  j = 0; j < img.rows; j++)
		{
			int A_r = img.at<Vec3b>(j, i)[0];
			int A_g = img.at<Vec3b>(j, i)[1];
			int A_b = img.at<Vec3b>(j, i)[2];
			int B_r = overlay.at<Vec3b>(floor((int)j * ratio_y),floor((int) i * ratio_x))[0];
			int B_g = overlay.at<Vec3b>(floor((int)j * ratio_y), floor((int)i * ratio_x))[1];
			int B_b = overlay.at<Vec3b>(floor((int)j * ratio_y), floor((int)i * ratio_x))[2];
			float C_r, C_g, C_b;
			C_r = B_r <= 128 ? (A_r * B_r) / 128 + ((double)A_r / 255) * ((double)A_r / 255) * (255 - 2 * B_r) :
				A_r * (255 - B_r) / 128 + sqrt((double)A_r / 255) * (2 * B_r - 255);
			C_g = B_g <= 128 ? (A_g * B_g) / 128 + ((double)A_g / 255) * ((double)A_g / 255) * (255 - 2 * B_g) :
				A_g * (255 - B_g) / 128 + sqrt((double)A_g / 255) * (2 * B_g - 255);
			C_b = B_b <= 128 ? (A_b * B_b) / 128 + ((double)A_b / 255) * ((double)A_b / 255) * (255 - 2 * B_b) :
				A_b * (255 - B_b) / 128 + sqrt((double)A_b / 255) * (2 * B_b - 255);

			/*C_r = A_r <= 128 ? (A_r * B_r) / 255 : 255 - (255 - A_r) * (255 - B_r) / 128;
			C_g = A_g <= 128 ? (A_g * B_g) / 255 : 255 - (255 - A_g) * (255 - B_g) / 128;
			C_b = A_b <= 128 ? (A_b * B_b) / 255 : 255 - (255 - A_b) * (255 - B_b) / 128;*/
			img.at<Vec3b>(j, i)[0] = common.checkOverFlow((int)C_r);
			img.at<Vec3b>(j, i)[1] = common.checkOverFlow((int)C_g);
			img.at<Vec3b>(j, i)[2] = common.checkOverFlow((int)C_b);
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
	Mat gray0, gray1;
	cvtColor(img, gray0, CV_RGB2GRAY);
	addWeighted(gray0, -1, NULL, 0, 255, gray1);

	GaussianBlur(gray1, gray1, Size(11, 11), 0);

	//ÈÚºÏ£ºÑÕÉ«¼õµ­  
	Mat img2(gray1.size(), CV_8UC1);
	for (int y = 0; y< img2.rows; y++)
	{

		uchar* P0 = gray0.ptr<uchar>(y);
		uchar* P1 = gray1.ptr<uchar>(y);
		uchar* P = img2.ptr<uchar>(y);
		for (int x = 0; x< img2.cols; x++)
		{
			int tmp0 = P0[x];
			int tmp1 = P1[x];
			P[x] = (uchar)min((tmp0 + (tmp0*tmp1) / (256 - tmp1)), 255);
		}

	}

	img = img2;
}

void Filter::film(Mat &img){
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img.at<Vec3b>(i, j)[0] = 255 - img.at<Vec3b>(i, j)[0];
			img.at<Vec3b>(i, j)[1] = 255 - img.at<Vec3b>(i, j)[1];
			img.at<Vec3b>(i, j)[2] = 255 - img.at<Vec3b>(i, j)[2];
		}
	}
}