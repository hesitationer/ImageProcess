#include "frequency_filter.h"

FrequencyFilter::FrequencyFilter(){

}

FrequencyFilter::~FrequencyFilter(){

}

void FrequencyFilter::blur(Mat &img, int n, float d0){

	Mat gray(img.rows, img.cols, CV_8UC1);
	Mat gray1(img.rows, img.cols, CV_8UC1);
	Mat gray2(img.rows, img.cols, CV_8UC1);

	for (int i = 0; i < img.rows && i < gray.rows; i++)
	{
		for (int j = 0; j < img.cols && j < gray.cols;  j++){
			gray.at<uchar>(i, j) = img.at<Vec3b>(i, j)[0];
			gray1.at<uchar>(i, j) = img.at<Vec3b>(i, j)[1];
			gray2.at<uchar>(i, j) = img.at<Vec3b>(i, j)[2];
		}
	}
	doDft(gray, n, d0, true, 0);
	doDft(gray1, n, d0, true, 0);
	doDft(gray2, n, d0, true, 0);
	for (int i = 0; i < img.rows && i < gray.rows; i++)
	{
		for (int j = 0; j < img.cols && j < gray.cols; j++){
			float b = gray.at<float>(i, j);
			float g = gray1.at<float>(i, j);
			float r = gray2.at<float>(i, j);
			img.at<Vec3b>(i, j)[0] = (int)(b * 255) ;
			img.at<Vec3b>(i, j)[1] = (int)(g * 255);
			img.at<Vec3b>(i, j)[2] = (int)(r * 255);
		}
	}
	
	/*Mat imgGray;
	cvtColor(img, imgGray, CV_BGR2GRAY);
	doDft(imgGray, n, d0);*/

}


void shiftDFT(Mat& fImage)
{
	Mat tmp, q0, q1, q2, q3;

	// first crop the image, if it has an odd number of rows or columns

	fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols / 2;
	int cy = fImage.rows / 2;

	// rearrange the quadrants of Fourier image
	// so that the origin is at the image center

	q0 = fImage(Rect(0, 0, cx, cy));
	q1 = fImage(Rect(cx, 0, cx, cy));
	q2 = fImage(Rect(0, cy, cx, cy));
	q3 = fImage(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

/******************************************************************************/

// create a 2-channel butterworth low-pass filter with radius D, order n
// (assumes pre-aollocated size of dft_Filter specifies dimensions)

void FrequencyFilter::createButterworthLowpassFilter(Mat &dft_Filter, int D, int n, bool low, float a)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	// based on the forumla in the IP notes (p. 130 of 2009/10 version)
	// see also HIPR2 on-line

	for (int i = 0; i < dft_Filter.rows; i++)
	{
		for (int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double)sqrt(pow((i - centre.x), 2.0) + pow((double)(j - centre.y), 2.0));
			if (low)
			{
				tmp.at<float>(i, j) = (float)
					(1 / (1 + pow((double)(radius / D), (double)(2 * n))));
			}
			else
			{
				tmp.at<float>(i, j) = (float)
					(1 / (1 + pow((double)(D / radius), (double)(2 * n)))) + a;
			}
		}
	}

	Mat toMerge[] = { tmp, tmp };
	merge(toMerge, 2, dft_Filter);
}


void FrequencyFilter::doDft(Mat &img, int n, float d0, bool low, float a)
{

	Mat imgOutput;	// image object(s)

	Mat padded;		// fourier image objects and arrays
	Mat complexImg, filter, filterOutput;
	Mat planes[2], mag;

	int N, M; // fourier image sizes

	int radius = d0;				// low pass filter parameter
	int order = n;				// low pass filter parameter


	// setup the DFT image sizes

	M = getOptimalDFTSize(img.rows);
	N = getOptimalDFTSize(img.cols);

	//cvtColor(img, imgGray, CV_BGR2GRAY);

	// setup the DFT images

	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
	planes[0] = Mat_<float>(padded);
	planes[1] = Mat::zeros(padded.size(), CV_32F);

	merge(planes, 2, complexImg);

	// do the DFT

	dft(complexImg, complexImg);

	// construct the filter (same size as complex image)

	filter = complexImg.clone();
	createButterworthLowpassFilter(filter, radius, order, low, a);

	// apply filter
	shiftDFT(complexImg);
	mulSpectrums(complexImg, filter, complexImg, 0);
	shiftDFT(complexImg);


	// do inverse DFT on filtered image

	idft(complexImg, complexImg);

	// split into planes and extract plane 0 as output image

	split(complexImg, planes);
	normalize(planes[0], imgOutput, 0, 1, CV_MINMAX);

	// ***

	// display image in window

	img = imgOutput;
}

void FrequencyFilter::sharpen(Mat &img, int n, int d0, float a){
	Mat gray(img.rows, img.cols, CV_8UC1);
	Mat gray1(img.rows, img.cols, CV_8UC1);
	Mat gray2(img.rows, img.cols, CV_8UC1);

	for (int i = 0; i < img.rows && i < gray.rows; i++)
	{
		for (int j = 0; j < img.cols && j < gray.cols; j++){
			gray.at<uchar>(i, j) = img.at<Vec3b>(i, j)[0];
			gray1.at<uchar>(i, j) = img.at<Vec3b>(i, j)[1];
			gray2.at<uchar>(i, j) = img.at<Vec3b>(i, j)[2];
		}
	}
	doDft(gray, n, d0, false, a);
	doDft(gray1, n, d0, false, a);
	doDft(gray2, n, d0, false, a);
	for (int i = 0; i < img.rows && i < gray.rows; i++)
	{
		for (int j = 0; j < img.cols && j < gray.cols; j++){
			float b = gray.at<float>(i, j);
			float g = gray1.at<float>(i, j);
			float r = gray2.at<float>(i, j);
			img.at<Vec3b>(i, j)[0] = (int)(b * 255);
			img.at<Vec3b>(i, j)[1] = (int)(g * 255);
			img.at<Vec3b>(i, j)[2] = (int)(r * 255);
		}
	}
	
	imageEnhancement.histEquTrans(img);
}



