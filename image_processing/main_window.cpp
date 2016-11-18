#include <QPainter>
#include <QVBoxLayout>
#include <QMessageBox>
#include "main_window.h"

Main_window::Main_window(QWidget *parent)
	:QWidget(parent)
{
	imgLabel = new MyImageLabel(tr("open an image "), this);
	imgLabel->window = this;
	showImageLabel = new QLabel(tr("show the image that edited"), this);

	//toolbar的相应的选择区
	rotationWidget = new QWidget(this);
	cutWidget = new QWidget(this);
	createActionInRotation();
	createActionInCut();
	lightWidget = new QWidget(this);
	saturationWidget = new QWidget(this);
	toneWidget = new QWidget(this);
	linearTransWidget = new QWidget(this);
	piecewiseTransWidget = new QWidget(this);
	nonlinearTransWidget = new QWidget(this);
	histEquWidget = new QWidget(this);
	histSpecWidget = new QWidget(this);
	medianFilterWidget = new QWidget(this);
	gaussianBlurWidget = new QWidget(this);
	sharpenWidget = new QWidget(this);
	filterWidget = new QWidget(this);

	createActionInLight();
	createActionInSaturation();
	createActionInTone();
	createActionInLinearTrans();
	createActionInPieceWiseLinearTrans();
	createActionInNonlinearTrans();
	createActionHistEquTrans();
	createActionInHistSpecTrans();
	createActionInMedianFilter();
	createActionInGaussianBlur();
	createActionInSharpen();
	createActionInFilter();

	imgBox = new QGroupBox();
	QHBoxLayout *imgBoxLayout = new QHBoxLayout;
	imgBoxLayout->addWidget(imgLabel);
	imgBoxLayout->addWidget(showImageLabel);
	imgBox->setLayout(imgBoxLayout);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(rotationWidget);
	layout->addWidget(cutWidget);
	layout->addWidget(lightWidget);
	layout->addWidget(saturationWidget);
	layout->addWidget(toneWidget);
	layout->addWidget(linearTransWidget);
	layout->addWidget(piecewiseTransWidget);
	layout->addWidget(nonlinearTransWidget);
	layout->addWidget(histEquWidget);
	layout->addWidget(histSpecWidget);
	layout->addWidget(medianFilterWidget);
	layout->addWidget(gaussianBlurWidget);
	layout->addWidget(sharpenWidget);
	layout->addWidget(filterWidget);
	layout->addWidget(imgBox);
	this->setLayout(layout);
	hideToolBar();
	rotationWidget->show();

	
	imgLabel->setAlignment(Qt::AlignLeft);
	showImageLabel->setAlignment(Qt::AlignLeft);
	imgBox->setFixedHeight(700);
}

Main_window::~Main_window()
{

}

void Main_window::loadImages()
{
	oldImg = imread(path.toStdString());
	drawImages(oldImg);
}

void Main_window::drawImages(Mat img)
{
	if (first)
	{
		showImageLabel->clear();
		imgLabel->clear();
		cvtColor(img, img, CV_BGR2RGB);
		QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
		QPixmap pix = QPixmap::fromImage(imdisplay);
		imgLabel->setPixmap(pix);
		cvtColor(img, img, CV_RGB2BGR);
		imgLabel->width = img.cols;
		imgLabel->height = img.rows;

		first = false;
		return;
	}
	//cv::resize(img, img, Size(512, 384), 0, 0, INTER_LINEAR);
	showImageLabel->clear();
	cvtColor(img, img, CV_BGR2RGB);
	QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
	QPixmap pix = QPixmap::fromImage(imdisplay);
	showImageLabel->setPixmap(pix);
	cvtColor(img, img, CV_RGB2BGR);
}

void Main_window::saveImages(string filename, Mat img)
{
	imwrite(filename, img);
}

void Main_window::createActionInRotation()
{
	angleLabel = new QLabel(tr("The degree of rotation to the right"));
	angleEdit = new QLineEdit;
	angleLabel->setBuddy(angleEdit);
	angleEdit->setMaximumWidth(50);
	rotationOkButton = new QPushButton(tr("&Ok"));
	connect(rotationOkButton, &QPushButton::clicked, this, &Main_window::clickRotationOk);
	flipHorizontalButton = new QPushButton(tr("&Flip Horizontal"));
	connect(flipHorizontalButton, &QPushButton::clicked, this, &Main_window::clickFlipHorizontal);

	flipVerticalButton = new QPushButton(tr("&Flip Vertical"));
	connect(flipVerticalButton, &QPushButton::clicked, this, &Main_window::clickFlipVertical);

	rotate90 = new QPushButton(tr("&Rotate 90 degree"));
	connect(rotate90, &QPushButton::clicked, this, &Main_window::clickRotate90);

	rotate180 = new QPushButton(tr("&Rotate 180 degree"));
	connect(rotate180, &QPushButton::clicked, this, &Main_window::clickRotate180);

	rotationButtonBox = new QGroupBox(tr("Rotation"));
	rotationButtonBox->setFixedHeight(100);
	QHBoxLayout *buttonBoxLayout = new QHBoxLayout();
	buttonBoxLayout->addWidget(rotate90);
	buttonBoxLayout->addWidget(rotate180);
	buttonBoxLayout->addWidget(flipHorizontalButton);
	buttonBoxLayout->addWidget(flipVerticalButton);
	buttonBoxLayout->addWidget(angleLabel);
	buttonBoxLayout->addWidget(angleEdit);
	buttonBoxLayout->addWidget(rotationOkButton);
	rotationButtonBox->setLayout(buttonBoxLayout);

	QHBoxLayout *rotationLayout = new QHBoxLayout;
	rotationLayout->addWidget(rotationButtonBox);
	rotationWidget->setLayout(rotationLayout);

}

void Main_window::createActionInLight()
{
	lightSlider = new QSlider(Qt::Horizontal, this);
	lightSlider->setSingleStep(1);
	lightSlider->setMinimum(-128);
	lightSlider->setMaximum(128);
	lightSlider->setValue(0);
	connect(lightSlider, &QSlider::valueChanged, this, &Main_window::lightSliderValueChanged);

	lightLineEdit = new QLineEdit(this);
	lightLineEdit->setEnabled(false);
	lightLineEdit->setText(tr("0"));
	lightLineEdit->setAlignment(Qt::AlignCenter);
	lightOkButton = new QPushButton(tr("Ok"), this);
	connect(lightOkButton, &QPushButton::clicked, this, &Main_window::clickLightOkButton);

	lightGroupBox = new QGroupBox(tr("Light"));
	lightGroupBox->setFixedHeight(100);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(lightSlider);
	layout->addWidget(lightLineEdit);
	layout->addWidget(lightOkButton);
	lightGroupBox->setLayout(layout);

	QHBoxLayout *lightLayout = new QHBoxLayout;
	lightLayout->addWidget(lightGroupBox);
	lightWidget->setLayout(lightLayout);
}

void Main_window::createActionInSaturation()
{
	saturationSlider = new QSlider(Qt::Horizontal, this);
	saturationSlider->setSingleStep(1);
	saturationSlider->setMinimum(-50);
	saturationSlider->setMaximum(50);
	saturationSlider->setValue(0);
	connect(saturationSlider, &QSlider::valueChanged, this, &Main_window::saturationSliderValueChanged);

	saturationLineEdit = new QLineEdit(this);
	saturationLineEdit->setEnabled(false);
	saturationLineEdit->setText(tr("0"));
	saturationLineEdit->setAlignment(Qt::AlignCenter);
	saturationOkButton = new QPushButton(tr("Ok"), this);
	connect(saturationOkButton, &QPushButton::clicked, this, &Main_window::clickSaturationOkButton);

	
	saturationGroupBox = new QGroupBox(tr("Saturation"));
	saturationGroupBox->setFixedHeight(100);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(saturationSlider);
	layout->addWidget(saturationLineEdit);
	layout->addWidget(saturationOkButton);
	saturationGroupBox->setLayout(layout);

	QHBoxLayout *saturationLayout = new QHBoxLayout;
	saturationLayout->addWidget(saturationGroupBox);
	saturationWidget->setLayout(saturationLayout);
}

void Main_window::createActionInTone()
{
	toneSlider = new QSlider(Qt::Horizontal, this);
	toneSlider->setSingleStep(1);
	toneSlider->setMinimum(-180);
	toneSlider->setMaximum(180);
	toneSlider->setValue(0);
	connect(toneSlider, &QSlider::valueChanged, this, &Main_window::toneSliderValueChanged);

	toneLineEdit = new QLineEdit(this);
	toneLineEdit->setEnabled(false);
	toneLineEdit->setText(tr("0"));
	toneLineEdit->setAlignment(Qt::AlignCenter);
	toneOkButton = new QPushButton(tr("Ok"), this);
	connect(toneOkButton, &QPushButton::clicked, this, &Main_window::clickToneOkButton);
	
	toneGroupBox = new QGroupBox(tr("Tone"));
	toneGroupBox->setFixedHeight(100);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(toneSlider);
	layout->addWidget(toneLineEdit);
	layout->addWidget(toneOkButton);
	toneGroupBox->setLayout(layout);

	QHBoxLayout *toneLayout = new QHBoxLayout;
	toneLayout->addWidget(toneGroupBox);
	toneWidget->setLayout(toneLayout);
}

void Main_window::createActionInLinearTrans()
{
	gradientLabel = new QLabel(tr("a"));
	biasLabel = new QLabel(tr("b"));
	gradientLineEdit = new QLineEdit(this);
	gradientLineEdit->setAlignment(Qt::AlignCenter);

	biasLineEdit = new QLineEdit(this);
	biasLineEdit->setAlignment(Qt::AlignCenter);

	linearTransOkButton = new QPushButton(tr("Ok"), this);
	connect(linearTransOkButton, &QPushButton::clicked, this, &Main_window::clickLinearTransOkButton);

	linearTransGroupBox = new QGroupBox(tr("Linear Transformation"));
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(gradientLabel);
	layout->addWidget(gradientLineEdit);
	layout->addWidget(biasLabel);
	layout->addWidget(biasLineEdit);
	layout->addWidget(linearTransOkButton);
	linearTransGroupBox->setLayout(layout);
	linearTransGroupBox->setFixedHeight(100);
	QHBoxLayout *lay = new QHBoxLayout;
	lay->addWidget(linearTransGroupBox);
	linearTransWidget->setLayout(lay);

}

void Main_window::createActionInPieceWiseLinearTrans()
{
	xRangeLabel = new QLabel(tr("the range of X"));
	xRangeLineEdit = new QLineEdit(this);
	xRangeLineEdit->setAlignment(Qt::AlignCenter);

	gradientLabelPieceWise = new QLabel("a");
	gradientLineEditPieceWise = new QLineEdit(this);
	gradientLineEditPieceWise->setAlignment(Qt::AlignCenter);

	biasLabelPieceWise = new QLabel(tr("b"));
	biasLineEditPieceWise = new QLineEdit(this);
	biasLineEditPieceWise->setAlignment(Qt::AlignCenter);
	pieceWiseTransOkButton = new QPushButton(tr("Ok"), this);
	connect(pieceWiseTransOkButton, &QPushButton::clicked, this, &Main_window::clickPieceWiseTransOkButton);
	piecewiseGroupBox = new QGroupBox(tr("Piecewise Linear Transformation"));

	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(xRangeLabel);
	groupBoxLayout->addWidget(xRangeLineEdit);
	groupBoxLayout->addWidget(gradientLabelPieceWise);
	groupBoxLayout->addWidget(gradientLineEditPieceWise);
	groupBoxLayout->addWidget(biasLabelPieceWise);
	groupBoxLayout->addWidget(biasLineEditPieceWise);
	groupBoxLayout->addWidget(pieceWiseTransOkButton);
	piecewiseGroupBox->setLayout(groupBoxLayout);
	piecewiseGroupBox->setFixedHeight(100);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(piecewiseGroupBox);
	piecewiseTransWidget->setLayout(layout);
	
}

void Main_window::createActionInNonlinearTrans()
{
	aLabel = new QLabel(tr("a"));
	bLabel = new QLabel(tr("b"));
	cLabel = new QLabel(tr("c"));
	gamaLabel = new QLabel(tr("gama"));

	aLineEdit = new QLineEdit(this);
	aLineEdit->setAlignment(Qt::AlignCenter);
	bLineEdit = new QLineEdit(this);
	bLineEdit->setAlignment(Qt::AlignCenter);
	cLineEdit = new QLineEdit(this);
	cLineEdit->setAlignment(Qt::AlignCenter);
	gamaLineEdit = new QLineEdit(this);
	gamaLineEdit->setAlignment(Qt::AlignCenter);

	nonLinearTransExpButton = new QPushButton(tr("Exp"), this);
	nonLinearTransLogButton = new QPushButton(tr("Log"), this);
	nonLinearTransGamaButton = new QPushButton(tr("Gama"), this);
	connect(nonLinearTransExpButton, &QPushButton::clicked, this, &Main_window::clickNonLinearTransExpButton);
	connect(nonLinearTransLogButton, &QPushButton::clicked, this, &Main_window::clickNonLinearTransLogButton);
	connect(nonLinearTransGamaButton, &QPushButton::clicked, this, &Main_window::clickNonLinearTransGamaButton);

	nonlinearGroupBox = new QGroupBox(tr("Nonlinear Transformation"));
	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(aLabel);
	layout1->addWidget(aLineEdit);
	layout1->addWidget(bLabel);
	layout1->addWidget(bLineEdit);
	layout1->addWidget(cLabel);
	layout1->addWidget(cLineEdit);

	QHBoxLayout *layout2 = new QHBoxLayout;

	layout2->addWidget(gamaLabel);
	layout2->addWidget(gamaLineEdit);
	layout2->addWidget(nonLinearTransExpButton);
	layout2->addWidget(nonLinearTransLogButton);
	layout2->addWidget(nonLinearTransGamaButton);

	QVBoxLayout *groupBoxLayout = new QVBoxLayout;
	groupBoxLayout->addLayout(layout1);
	groupBoxLayout->addLayout(layout2);
	nonlinearGroupBox->setLayout(groupBoxLayout);
	nonlinearGroupBox->setFixedHeight(100);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(nonlinearGroupBox);
	nonlinearTransWidget->setLayout(layout);
}

void Main_window::createActionHistEquTrans()
{
	histEquOkButton = new QPushButton(tr("Equalization"), this);
	connect(histEquOkButton, &QPushButton::clicked, this, &Main_window::clickHistEquOkButton);
	histEquGroupBox = new QGroupBox(tr("Histogram Equalization"));

	viewHistEquButton = new QPushButton(tr("View the histogram"));
	connect(viewHistEquButton, &QPushButton::clicked, this, &Main_window::clickViewHistEquButton);

	viewAfterHistEquButton = new QPushButton(tr("View the histogram of the equalization"));
	connect(viewAfterHistEquButton, &QPushButton::clicked, this, &Main_window::clickViewAfterHistEquButton);

	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(viewHistEquButton);
	groupBoxLayout->addWidget(histEquOkButton);
	groupBoxLayout->addWidget(viewAfterHistEquButton);
	histEquGroupBox->setLayout(groupBoxLayout);
	histEquGroupBox->setFixedHeight(100);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(histEquGroupBox);
	histEquWidget->setLayout(layout);
}

void Main_window::createActionInHistSpecTrans()
{
	histSpecSelectImgButton = new QPushButton(tr("select an img"), this);
	connect(histSpecSelectImgButton, &QPushButton::clicked, this, &Main_window::clickHistSpecSelectImgButton);

	histSpecViewHistButton = new QPushButton(tr("view histogram"), this);
	connect(histSpecViewHistButton, &QPushButton::clicked, this, &Main_window::clickHistSpecViewHistButton);


	histSpecSMLButton = new QPushButton(tr("SML"), this);
	connect(histSpecSMLButton, &QPushButton::clicked, this, &Main_window::clickHistSpecSMLButton);

	histSpecGMLButton = new QPushButton(tr("GML"), this);
	connect(histSpecGMLButton, &QPushButton::clicked, this, &Main_window::clickHistSpecGMLButton);

	histSpecViewAfterHistButton = new QPushButton(tr("view histogram of edited image"));
	connect(histSpecViewAfterHistButton, &QPushButton::clicked, this, &Main_window::clickHistSpecViewAfterHistButton);

	histSpecGroupBox = new QGroupBox(tr("Histogram Specification"));



	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(histSpecSelectImgButton);
	groupBoxLayout->addWidget(histSpecViewHistButton);
	groupBoxLayout->addWidget(histSpecSMLButton);
	groupBoxLayout->addWidget(histSpecGMLButton);
	groupBoxLayout->addWidget(histSpecViewAfterHistButton);
	histSpecGroupBox->setLayout(groupBoxLayout);
	histSpecGroupBox->setFixedHeight(100);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(histSpecGroupBox);
	histSpecWidget->setLayout(layout);
}

void Main_window::createActionInMedianFilter()
{
	medianFilterTemplateSizeLabel = new QLabel(tr("Template Size"));
	medianFilterTemplateSizeLineEdit = new QLineEdit;
	medianFilterTemplateSizeLineEdit->setAlignment(Qt::AlignCenter);

	medianFilterTemplateShapeButton = new QPushButton(tr("select template shape"), this);
	connect(medianFilterTemplateShapeButton, &QPushButton::clicked, this, &Main_window::clickMedianFilterTemplateShapeButton);

	medianFilterOkButton = new QPushButton(tr("Ok"), this);
	connect(medianFilterOkButton, &QPushButton::clicked, this, &Main_window::clickMedianFilterOkButton);

	medianFilterGroupBox = new QGroupBox(tr("Median Filter"));

	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(medianFilterTemplateSizeLabel);
	groupBoxLayout->addWidget(medianFilterTemplateSizeLineEdit);
	groupBoxLayout->addWidget(medianFilterTemplateShapeButton);
	groupBoxLayout->addWidget(medianFilterOkButton);
	medianFilterGroupBox->setFixedHeight(100);
	medianFilterGroupBox->setLayout(groupBoxLayout);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(medianFilterGroupBox);
	medianFilterWidget->setLayout(layout);
}

void  Main_window::createActionInGaussianBlur()
{
	gaussianBlurOkButton = new QPushButton("Ok", this);
	connect(gaussianBlurOkButton, &QPushButton::clicked, this, &Main_window::clickGaussianBlurOkButton);

	gaussianBlurRadiusLabel = new QLabel(tr("sigma"));
	gaussianBlurRadiusLineEdit = new QLineEdit;
	gaussianBlurRadiusLineEdit->setAlignment(Qt::AlignCenter);

	gaussianBlurTemplateSizeLabel = new QLabel("template size");
	gaussianBlurTemplateSizeLineEdit = new	QLineEdit;
	gaussianBlurTemplateSizeLineEdit->setAlignment(Qt::AlignCenter);

	gaussianBlurGroupBox = new QGroupBox(tr("Gaussian Blur"));
	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(gaussianBlurTemplateSizeLabel);
	groupBoxLayout->addWidget(gaussianBlurTemplateSizeLineEdit);
	groupBoxLayout->addWidget(gaussianBlurRadiusLabel);
	groupBoxLayout->addWidget(gaussianBlurRadiusLineEdit);
	groupBoxLayout->addWidget(gaussianBlurOkButton);
	gaussianBlurGroupBox->setLayout(groupBoxLayout);
	gaussianBlurGroupBox->setFixedHeight(100);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(gaussianBlurGroupBox);
	gaussianBlurWidget->setLayout(layout);
}

void Main_window::createActionInSharpen()
{
	sharpenThresholdLabel = new QLabel(tr("threshold"));
	sharpenThresholeLineEdit = new QLineEdit;
	sharpenThresholeLineEdit->setAlignment(Qt::AlignCenter);

	sharpenIncrementalLabel = new QLabel(tr("incremental"));
	sharpenIncrementalLineEdit = new QLineEdit;
	sharpenIncrementalLineEdit->setAlignment(Qt::AlignCenter);

	sharpenRobertsButton = new QPushButton(tr("Roberts"), this);
	connect(sharpenRobertsButton, &QPushButton::clicked, this, &Main_window::clickSharpenRobertsButton);

	sharpenPrewittButton = new QPushButton(tr("Prewitt"), this);
	connect(sharpenPrewittButton, &QPushButton::clicked, this, &Main_window::clickSharpenPrewittButton);

	sharpenSobelButton = new QPushButton(tr("Sobel"), this);
	connect(sharpenSobelButton, &QPushButton::clicked, this, &Main_window::clickSharpenSobelButton);

	sharpenLaplaceButton = new QPushButton(tr("Laplace"), this);
	connect(sharpenLaplaceButton, &QPushButton::clicked, this, &Main_window::clickSharpenLaplaceButton);

	sharpenGroupBox = new QGroupBox(tr("Sharpen"));
	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(sharpenThresholdLabel);
	groupBoxLayout->addWidget(sharpenThresholeLineEdit);
	groupBoxLayout->addWidget(sharpenIncrementalLabel);
	groupBoxLayout->addWidget(sharpenIncrementalLineEdit);
	groupBoxLayout->addWidget(sharpenRobertsButton);
	groupBoxLayout->addWidget(sharpenPrewittButton);
	groupBoxLayout->addWidget(sharpenSobelButton);
	groupBoxLayout->addWidget(sharpenLaplaceButton);
	sharpenGroupBox->setLayout(groupBoxLayout);
	sharpenGroupBox->setFixedHeight(100);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(sharpenGroupBox);
	sharpenWidget->setLayout(layout);
}

void Main_window::createActionInFilter()
{
	lomoFilterButton = new QPushButton(tr("Lomo"), this);
	connect(lomoFilterButton, &QPushButton::clicked, this, &Main_window::clickLomoFilterButton);

	colorReliefFilterButton = new QPushButton(tr("Color Relief"), this);
	connect(colorReliefFilterButton, &QPushButton::clicked, this, &Main_window::clickColorReliefFilterButton);

	pencilDrawingFilterButton = new QPushButton(tr("Penicl Drawing"), this);
	connect(pencilDrawingFilterButton, &QPushButton::clicked, this, &Main_window::clickPencilDrawingFilterButton);

	latticeFilterButton = new QPushButton(tr("Lattice"), this);
	connect(latticeFilterButton, &QPushButton::clicked, this, &Main_window::clickLatticeFilterButton);

	filterGroupBox = new QGroupBox(tr("Filter"));
	QHBoxLayout *groupBoxLayout = new QHBoxLayout;
	groupBoxLayout->addWidget(lomoFilterButton);
	groupBoxLayout->addWidget(colorReliefFilterButton);
	groupBoxLayout->addWidget(pencilDrawingFilterButton);
	groupBoxLayout->addWidget(latticeFilterButton);
	filterGroupBox->setLayout(groupBoxLayout);
	filterGroupBox->setFixedHeight(100);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(filterGroupBox);
	filterWidget->setLayout(layout);
}

void Main_window::showRotation()
{
	hideToolBar();
	rotationWidget->show();
}

void Main_window::showCutWidget()
{
	hideToolBar();
	cutWidget->show();
}

void Main_window::showLight()
{
	hideToolBar();
	lightWidget->show();
}

void Main_window::showSaturation()
{
	hideToolBar();
	saturationWidget->show();
}

void Main_window::showTone()
{
	hideToolBar();
	toneWidget->show();
}

void Main_window::showLinearTrans()
{
	hideToolBar();
	linearTransWidget->show();
}

void Main_window::showPieceWiseLinearTrans()
{
	hideToolBar();
	piecewiseTransWidget->show();
}

void Main_window::showNonlinearTrans()
{
	hideToolBar();
	nonlinearTransWidget->show();
}

void Main_window::showHistEquTrans()
{
	hideToolBar();
	histEquWidget->show();
}

void Main_window::showHistSpecTrans()
{
	hideToolBar();
	histSpecWidget->show();
}

void Main_window::showMedianFilter()
{
	hideToolBar();
	medianFilterWidget->show();
}

void Main_window::showGaussianBlur()
{
	hideToolBar();
	gaussianBlurWidget->show();
}

void Main_window::showSharpen()
{
	hideToolBar();
	sharpenWidget->show();
}

void Main_window::showFilter()
{
	hideToolBar();
	filterWidget->show();
}
void Main_window::clickFlipHorizontal()
{
	if (!checkImage())
	{
		return;
	}
	img = oldImg.clone();
	rotation.flipHorizontal(img);
	drawImages(img);
	
}

void Main_window::clickFlipVertical()
{
	if (!checkImage())
	{
		return;
	}
	img = oldImg.clone();
	rotation.flipVertical(img);
	drawImages(img);
}

void Main_window::clickRotationOk()
{

	if (!checkImage())
	{
		return;
	}
	QString text = angleEdit->text();
	if (text == NULL || text.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the degree first"));
		return;
	}
	bool ok;
	int degree = text.toInt(&ok, 10);
	if (!ok)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the right degree"));
		return;
	}
	img = oldImg.clone();
	rotation.rotation_image(img, true, degree);
	drawImages(img);
}

bool Main_window::checkImage()
{
	if (path.isEmpty() || path.isNull())
	{
		QMessageBox::information(this,
			tr("tips"), tr("please first open an image") );
		return false;
	}
	return true;
}

void Main_window::clickRotate90()
{
	if (!checkImage())
	{
		return;
	}
	img = oldImg.clone();
	rotation.rotate90(img);
	drawImages(img);
}

void Main_window::clickRotate180()
{
	if (!checkImage())
	{
		return;
	}
	img = oldImg.clone();
	rotation.rotate180(img);
	drawImages(img);
}

void Main_window::createActionInCut()
{
	cutRectButton = new QPushButton(tr("&Rectangle Cut"));
	connect(cutRectButton, &QPushButton::clicked, this, &Main_window::clickCutRect);

	cutRoundButton = new QPushButton(tr("&Round Cut"));
	connect(cutRoundButton, &QPushButton::clicked, this, &Main_window::clickCutRound);


	cutPolygonButton = new QPushButton(tr("&Polygon Cut"));
	connect(cutPolygonButton, &QPushButton::clicked, this, &Main_window::clickCutPolygon);

	cutPolygonOkButton = new QPushButton(tr("&Polygon Ok"));
	connect(cutPolygonOkButton, &QPushButton::clicked, this, &Main_window::clickCutPolygonOk);

	cutButtonBox = new QGroupBox(tr("&Cut"));
	cutButtonBox->setFixedHeight(100);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(cutRectButton);
	layout->addWidget(cutRoundButton);
	layout->addWidget(cutPolygonButton);
	layout->addWidget(cutPolygonOkButton);
	cutButtonBox->setLayout(layout);

	QHBoxLayout *cutLayout = new QHBoxLayout();
	cutLayout->addWidget(cutButtonBox);
	cutWidget->setLayout(cutLayout);
}

void Main_window::clickCutRect()
{
	if (!checkImage())
	{
		return;
	}
	imgLabel->setCursor(Qt::CrossCursor);
	imgLabel->scribbling = true;
	imgLabel->draw_flag = 1;
}

void Main_window::clickCutRound()
{
	if (!checkImage())
	{
		return;
	}
	imgLabel->setCursor(Qt::CrossCursor);
	imgLabel->scribbling = true;
	imgLabel->draw_flag = 2;
}

void Main_window::clickCutPolygon()
{
	if (!checkImage())
	{
		return;
	}
	imgLabel->setCursor(Qt::CrossCursor);
	imgLabel->scribbling = true;
	imgLabel->draw_flag = 3;
}

void Main_window::clickCutPolygonOk()
{
	if (!checkImage())
	{
		return;
	}
	if (imgLabel->points.size() < 3)
	{
		QMessageBox::information(this, tr("tips"), tr("nodes is less than 3"));
		imgLabel->polygon_flag = 0;
		imgLabel->draw_flag = 0;
		imgLabel->update();
		imgLabel->points.clear();
		return;
	}
	imgLabel->polygon_flag = 1;
	imgLabel->setCursor(Qt::ArrowCursor);
	imgLabel->update();
	if (QMessageBox::question(this, tr("confirm"), tr("Are you true to cut the image?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
	{
		cutPolygon(imgLabel->points);
	}
	imgLabel->points.clear();
	imgLabel->polygon_flag = 0;
	imgLabel->draw_flag = 0;
	imgLabel->update();
}

void Main_window::hideToolBar()
{
	rotationWidget->hide();
	cutWidget->hide();
	lightWidget->hide();
	saturationWidget->hide();
	toneWidget->hide();
	linearTransWidget->hide();
	piecewiseTransWidget->hide();
	nonlinearTransWidget->hide();
	histEquWidget->hide();
	histSpecWidget->hide();
	medianFilterWidget->hide();
	gaussianBlurWidget->hide();
	sharpenWidget->hide();
	filterWidget->hide();
}

void Main_window::cutRect(int x, int y, int w, int h)
{
	img = oldImg.clone();
	cutImage.cutRect(img, x, y, w, h);
	drawImages(img);
	imgLabel->draw_flag = 0;
	imgLabel->update();
}

void Main_window::cutRound(QPoint center, int r)
{
	img = oldImg.clone();
	cutImage.cutRound(img, center, r);
	drawImages(img);
	imgLabel->draw_flag = 0;
	imgLabel->update();
}

void Main_window::cutPolygon(QVector<QPoint> points)
{
	img = oldImg.clone();
	cutImage.cutPolygon(img, points);
	drawImages(img);
	imgLabel->draw_flag = 0;
	imgLabel->update();
}

void Main_window::clickLightOkButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	int value = lightSlider->value();
	hsi.changeLight(img, value);
	drawImages(img);
}

void Main_window::clickSaturationOkButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	int value = saturationSlider->value();
	hsi.changeSaturation(img, value);
	drawImages(img);

}

void Main_window::clickToneOkButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	int value = toneSlider->value();
	hsi.changeTone(img, value);
	drawImages(img);

}

void Main_window::clickLinearTransOkButton()
{
	if (!checkImage())
	{
		return;
	}
	QString  gridString = gradientLineEdit->text();
	if (gridString.isNull() || gridString.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the gradient first"));
		return;
	}

	QString biasStr = biasLineEdit->text();
	if (biasStr.isNull() || biasStr.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the bias first"));
		return;
	}
	bool ok;
	float grid = gridString.toFloat(&ok);
	if (!ok)
	{
		QMessageBox::information(this, tr("tips"), tr("please input correct gradient"));
		return;
	}

	float bias = biasStr.toFloat(&ok);
	if (!ok)
	{
		QMessageBox::information(this, tr("tips"), tr("please input correct bias"));
		return;
	}
	img = oldImg.clone();
	imageEnhancement.linearTrans(img, grid, bias);
	drawImages(img);
}

void Main_window::clickPieceWiseTransOkButton()
{
	if (!checkImage())
	{
		return;
	}

	QString xRangeStr = xRangeLineEdit->text();
	QString gradStr = gradientLineEditPieceWise->text();
	QString biasStr = biasLineEditPieceWise->text();
	if (xRangeStr.isEmpty() || xRangeStr.isNull() || gradStr.isEmpty() || gradStr.isNull() || 
		biasStr.isEmpty() || biasStr.isNull())
	{
		QMessageBox::information(this, tr("tips"), tr("please input  all the parameter"));
		return;
	}

	QStringList  xRangeList = xRangeStr.split(',');
	QStringList gradList = gradStr.split(',');
	QStringList biasList = biasStr.split(',');

	QVector<int> xRange;
	for (int i = 0; i < xRangeList.size(); i++)
	{
		bool ok;
		int temp = xRangeList.at(i).toInt(&ok);
		if (!ok)
		{
			QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
			return;
		}
		xRange.append(temp);
	}

	QVector<float> gradient;
	for (int i = 0; i < gradList.size(); i++)
	{
		bool ok;
		float temp = gradList.at(i).toFloat(&ok);
		if (!ok)
		{
			QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
			return;
		}
		gradient.append(temp);
	}

	QVector<float> bias;
	for (int i = 0; i < biasList.size(); i++)
	{
		bool ok;
		float temp = biasList.at(i).toFloat(&ok);
		if (!ok)
		{
			QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
			return;
		}
		bias.append(temp);
	}

	if (xRange.size() < 2 || xRange.at(0) != 0 || xRange.at(xRange.size() - 1 ) != 255 || gradient.size() != bias.size()
		|| xRange.size() != (gradient.size() + 1))
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
		return;
	}

	img = oldImg.clone();
	imageEnhancement.pieceWiseTrans(img, xRange, gradient, bias);
	drawImages(img);
}

void Main_window::clickNonLinearTransExpButton()
{
	if (!checkImage())
	{
		return;
	}
	QString aStr = aLineEdit->text();
	QString bStr = bLineEdit->text();
	QString cStr = cLineEdit->text();
	if (aStr.isEmpty() || aStr.isNull() || bStr.isEmpty() || bStr.isNull() || cStr.isNull() || cStr.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input  all the parameter"));
		return;
	}
	bool ok1, ok2, ok3;
	float a = aStr.toFloat(&ok1);
	float b = bStr.toFloat(&ok2);
	float c = cStr.toFloat(&ok3);
	if (!ok1 || !ok2 || !ok3)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
		return;
	}

	img = oldImg.clone();
	imageEnhancement.nonLinearExpTrans(img, a, b, c);
	drawImages(img);
}

void Main_window::clickNonLinearTransLogButton()
{

	if (!checkImage())
	{
		return;
	}
	QString cStr = cLineEdit->text();
	if ( cStr.isNull() || cStr.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input  all the parameter"));
		return;
	}
	bool ok3;
	float c = cStr.toFloat(&ok3);
	if (!ok3)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
		return;
	}

	img = oldImg.clone();
	imageEnhancement.nonLinearLogTrans(img, c);
	drawImages(img);
}

void Main_window::clickNonLinearTransGamaButton()
{
	if (!checkImage())
	{
		return;
	}

	QString gamaStr = gamaLineEdit->text();
	QString cStr = cLineEdit->text();
	if (gamaStr.isNull() || gamaStr.isEmpty() || cStr.isNull() || cStr.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input  all the parameter"));
		return;
	}

	bool ok1, ok2;
	float gama = gamaStr.toFloat(&ok1);
	float c = cStr.toFloat(&ok2);
	if (!ok1 || !ok2)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parameter"));
		return;
	}

	img = oldImg.clone();
	imageEnhancement.nonLinearGamaTrans(img, gama, c);
	drawImages(img);
}

void Main_window::clickHistEquOkButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	imageEnhancement.histEquTrans(img);
	drawImages(img);
}

void Main_window::clickHistSpecSMLButton()
{
	if (!checkImage())
	{
		return;
	}

	if (selectImg.empty())
	{
		QMessageBox::information(this, tr("tips"), tr("please select an image first"));
		return;
	}
	img = oldImg.clone();
	imageEnhancement.histSpecTrans(img, selectImgBHist, selectImgGHist, selectImgRHist);
	drawImages(img);
}

void Main_window::lightSliderValueChanged()
{
	int value = lightSlider->value();
	lightLineEdit->setText(QString::number(value));
}

void Main_window::saturationSliderValueChanged()
{
	int value = saturationSlider->value();
	saturationLineEdit->setText(QString::number(value));
}

void Main_window::toneSliderValueChanged()
{
	int value = toneSlider->value();
	toneLineEdit->setText(QString::number(value));
}


void Main_window::clickViewAfterHistEquButton()
{
	if (!checkImage())
	{
		return;
	}
	if (img.empty())
	{
		QMessageBox::information(this, tr("tips"), tr("please do the picture equalization first"));
		return;
	}
	float b[256];
	float g[256];
	float r[256];
	for (int i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
	}
	imageEnhancement.getHistOfImg(img, b, g, r, 256);

	BgrHistogram *hist = new BgrHistogram(this, b, g, r, tr("histogram of edited image"));
	hist->show();

}

void Main_window::clickViewHistEquButton()
{
	if (!checkImage())
	{
		return;
	}

	float b[256];
	float g[256];
	float r[256];
	for (int i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
	}
	imageEnhancement.getHistOfImg(oldImg, b, g, r, 256);
	
	BgrHistogram *hist = new BgrHistogram(this, b, g, r, tr("histogram of original image"));
	hist->show();

}

void Main_window::clickHistSpecGMLButton()
{
	if (!checkImage())
	{
		return;
	}

	if (selectImg.empty())
	{
		QMessageBox::information(this, tr("tips"), tr("please select an image first"));
		return;
	}
	img = oldImg.clone();
	imageEnhancement.histSpecGMLTrans(img, selectImgBHist, selectImgGHist, selectImgRHist);
	drawImages(img);
}

void Main_window::clickHistSpecSelectImgButton()
{
	if (!checkImage())
	{
		return;
	}
	QString path = QFileDialog::getOpenFileName(
		this,
		"Select one file to open",
		"",
		"Images (*.png *.xpm *.jpg)");

	if (!path.isEmpty() && !path.isNull()) {

		selectImg = imread(path.toStdString());

		QLabel *dialog = new QLabel();
		dialog->setWindowTitle(tr("selected image"));
		dialog->resize(600, 600);
		//dialog->show();
		cvtColor(selectImg, selectImg, CV_BGR2RGB);
		QImage imdisplay((uchar*)selectImg.data, selectImg.cols, selectImg.rows, selectImg.step, QImage::Format_RGB888);
		dialog->setPixmap(QPixmap::fromImage(imdisplay));
		cvtColor(selectImg, selectImg, CV_RGB2BGR);


		for (int i = 0; i < 256; i++)
		{
			selectImgBHist[i] = 0.0;
			selectImgGHist[i] = 0.0;
			selectImgRHist[i] = 0.0;
		}

		imageEnhancement.getHistOfImg(selectImg, selectImgBHist, selectImgGHist, selectImgRHist, 256);


		BgrHistogram *hist = new BgrHistogram(this, selectImgBHist, selectImgGHist, selectImgRHist, tr("histogram of selected image"));
		hist->show();
		imageEnhancement.getEqu(selectImgBHist);
		imageEnhancement.getEqu(selectImgGHist);
		imageEnhancement.getEqu(selectImgRHist);

	}
}

void Main_window::clickHistSpecViewAfterHistButton()
{
	if (!checkImage())
	{
		return;
	}
	if (img.empty())
	{
		QMessageBox::information(this, tr("tips"), tr("please do the picture specification first"));
		return;
	}
	float b[256];
	float g[256];
	float r[256];
	for (int i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
	}
	imageEnhancement.getHistOfImg(img, b, g, r, 256);

	BgrHistogram *hist = new BgrHistogram(this, b, g, r, tr("histogram of edited image"));
	hist->show();
}

void Main_window::clickHistSpecViewHistButton()
{
	if (!checkImage())
	{
		return;
	}

	float b[256];
	float g[256];
	float r[256];
	for (int i = 0; i < 256; i++)
	{
		b[i] = 0.0;
		g[i] = 0.0;
		r[i] = 0.0;
	}
	imageEnhancement.getHistOfImg(oldImg, b, g, r, 256);

	BgrHistogram *hist = new BgrHistogram(this, b, g, r, tr("histogram of original image"));
	hist->show();
}

void Main_window::clickMedianFilterOkButton()
{
	if (!checkImage())
	{
		return;
	}
	QString template_size_str = medianFilterTemplateSizeLineEdit->text();
	if (template_size_str.isEmpty() || template_size_str.isNull())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the template size first"));
		return;
	}
	bool ok;
	int template_size = template_size_str.toInt(&ok);
	if (!ok || template_size % 2 == 0)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct template size"));
		return;
	}

	if (medianTemplateSizeLast == -1 || medianTemplateSizeLast != template_size)
	{
		medianFilterTemplateShape = new bool*[template_size];
		for (int i = 0; i < template_size; i++)
		{
			medianFilterTemplateShape[i] = new bool[template_size];
			for (int j = 0; j < template_size; j++)
			{
				medianFilterTemplateShape[i][j] = true;
			}
		}
	}
	
	img = oldImg.clone();
	spatialFilter.medianFilter(img, template_size, medianFilterTemplateShape);
	drawImages(img);
	QMessageBox::information(this, tr("tips"), tr("success"));

}

void Main_window::clickMedianFilterTemplateShapeButton()
{
	if (!checkImage())
	{
		return;
	}

	QString template_size_str = medianFilterTemplateSizeLineEdit->text();
	if (template_size_str.isNull() || template_size_str.isEmpty())
	{
		QMessageBox::information(this,tr("tips"), tr("please input the template size first"));
		return;
	}
	bool ok;
	int template_size = template_size_str.toInt(&ok);
	if (!ok || template_size % 2 == 0)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the corrent template size"));
		return;
	}

	TemplateSizeDialog *dialog = new TemplateSizeDialog(template_size, this);
	dialog->show();

}

void Main_window::clickGaussianBlurOkButton()
{
	if (!checkImage())
	{
		return;
	}

	QString sigma_str = gaussianBlurRadiusLineEdit->text();
	QString template_size_str = gaussianBlurTemplateSizeLineEdit->text();
	if (sigma_str.isNull() || sigma_str.isEmpty() || template_size_str.isNull() || template_size_str.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the parm first"));
		return;
	}

	bool ok1, ok2;
	float sigma = sigma_str.toFloat(&ok1);
	int template_size = template_size_str.toInt(&ok2);
	if (!ok1 || !ok2)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parm"));
		return;
	}

	if (sigma < 0.1 || sigma > 250 || template_size % 2 != 1)
	{
		QMessageBox::information(this, tr("tips"), tr("the range of sigma is 0.1 ~ 250 and template size is the odd number"));
		return;
	}

	img = oldImg.clone();
	spatialFilter.gaussianBlur(img, sigma, template_size);
	drawImages(img);
	QMessageBox::information(this, tr("tips"), tr("success"));
}

void Main_window::clickSharpenRobertsButton()
{
	if (!checkImage())
	{
		return;
	}

	QString threshold_str = sharpenThresholeLineEdit->text();
	QString incremental_str = sharpenIncrementalLineEdit->text();
	if (threshold_str.isNull() || threshold_str.isEmpty() || incremental_str.isNull() || incremental_str.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the parm"));
		return;
	}

	bool ok1, ok2;
	int threshold = threshold_str.toInt(&ok1);
	int incremental = incremental_str.toInt(&ok2);
	if (!ok1 || !ok2)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parm"));
		return;
	}

	img = oldImg.clone();
	spatialFilter.sharpenRoberts(img, threshold, incremental);
	drawImages(img);
}

void Main_window::clickSharpenPrewittButton()
{
	if (!checkImage())
	{
		return;
	}

	QString threshold_str = sharpenThresholeLineEdit->text();
	QString incremental_str = sharpenIncrementalLineEdit->text();
	if (threshold_str.isNull() || threshold_str.isEmpty() || incremental_str.isNull() || incremental_str.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the parm"));
		return;
	}

	bool ok1, ok2;
	int threshold = threshold_str.toInt(&ok1);
	int incremental = incremental_str.toInt(&ok2);
	if (!ok1 || !ok2)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parm"));
		return;
	}

	img = oldImg.clone();
	spatialFilter.sharpenPrewitt(img, threshold, incremental);
	drawImages(img);
}

void Main_window::clickSharpenSobelButton()
{
	if (!checkImage())
	{
		return;
	}

	QString threshold_str = sharpenThresholeLineEdit->text();
	QString incremental_str = sharpenIncrementalLineEdit->text();
	if (threshold_str.isNull() || threshold_str.isEmpty() || incremental_str.isNull() || incremental_str.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the parm"));
		return;
	}

	bool ok1, ok2;
	int threshold = threshold_str.toInt(&ok1);
	int incremental = incremental_str.toInt(&ok2);
	if (!ok1 || !ok2)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parm"));
		return;
	}

	img = oldImg.clone();
	spatialFilter.sharpenSobel(img, threshold, incremental);
	drawImages(img);
}

void Main_window::clickSharpenLaplaceButton()
{
	if (!checkImage())
	{
		return;
	}

	QString threshold_str = sharpenThresholeLineEdit->text();
	QString incremental_str = sharpenIncrementalLineEdit->text();
	if (threshold_str.isNull() || threshold_str.isEmpty() || incremental_str.isNull() || incremental_str.isEmpty())
	{
		QMessageBox::information(this, tr("tips"), tr("please input the parm"));
		return;
	}

	bool ok1, ok2;
	int threshold = threshold_str.toInt(&ok1);
	int incremental = incremental_str.toInt(&ok2);
	if (!ok1 || !ok2)
	{
		QMessageBox::information(this, tr("tips"), tr("please input the correct parm"));
		return;
	}

	img = oldImg.clone();
	spatialFilter.sharpenLaplace(img, threshold, incremental);
	drawImages(img);
}

void Main_window::clickLomoFilterButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	Mat overlay = imread("overlay2.png");
	filter.lomo(img, overlay);
	drawImages(img);
}


void Main_window::clickColorReliefFilterButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	filter.grayscaleRelief(img);
	drawImages(img);
}

void Main_window::clickPencilDrawingFilterButton()
{
	if (!checkImage())
	{
		return;
	}

	img = oldImg.clone();
	filter.pencilDrawing(img);
	drawImages(img);
}

void Main_window::clickLatticeFilterButton()
{

}
