#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QScrollArea>
#include <QFileDialog>
#include <QPainter>
#include "ui_image_processing.h"
#include "rotation.h"
#include "image_label.h"
#include "cut_image.h"
#include "hsi.h"
#include "image_enhancement.h"
#include "bgr_histogram.h"
#include "template_size_dialog.h"
#include "spatial_filter.h"
#include "filter.h"
class Main_window : public QWidget
{
	Q_OBJECT
public:
	Main_window(QWidget *parent = 0);
	~Main_window();

	QString path;
	QString filename;
	MyImageLabel *imgLabel;
	QLabel *showImageLabel;
	bool first = true;
	int medianTemplateSizeLast = -1;




	void loadImages();
	void drawImages(Mat img);
	void saveImages(String filename, Mat img);
	void createActionInRotation();
	void showRotation();
	bool checkImage();
	void createActionInCut();
	void hideToolBar();
	void showCutWidget();

	//亮度，饱和度，色调
	void createActionInLight();
	void showLight();
	void createActionInSaturation();
	void showSaturation();
	void createActionInTone();
	void showTone();

	//cut
	void cutRect(int x, int y, int w, int h);
	void cutRound(QPoint center, int r);
	void cutPolygon(QVector<QPoint> points);

	//图像增强
	void createActionInLinearTrans();
	void createActionInPieceWiseLinearTrans();
	void createActionInNonlinearTrans();
	void createActionHistEquTrans();
	void createActionInHistSpecTrans();
	void showLinearTrans();
	void showPieceWiseLinearTrans();
	void showNonlinearTrans();
	void showHistEquTrans();
	void showHistSpecTrans();

	//空域滤波
	void createActionInMedianFilter();
	void createActionInGaussianBlur();
	void createActionInSharpen();
	void showMedianFilter();
	void showGaussianBlur();
	void showSharpen();

	//滤镜
	void createActionInFilter();
	void showFilter();

	Mat img;
	Mat oldImg;
	Mat selectImg;
	float selectImgBHist[256];
	float selectImgGHist[256];
	float selectImgRHist[256];
	bool **medianFilterTemplateShape;
private:
	QWidget *rotationWidget;
	QWidget *cutWidget;
	QWidget *lightWidget;
	QWidget *saturationWidget;
	QWidget *toneWidget;
	QWidget *linearTransWidget;
	QWidget *piecewiseTransWidget;
	QWidget *nonlinearTransWidget;
	QWidget *histEquWidget;
	QWidget *histSpecWidget;
	QWidget *filterWidget;


	//空域滤波
	QWidget *medianFilterWidget;
	QWidget *gaussianBlurWidget;
	QWidget *sharpenWidget;

	//action in rotationWidget
	QLabel *angleLabel;
	QLineEdit *angleEdit;
	QGroupBox *rotationButtonBox;
	QPushButton *rotationOkButton;
	QPushButton *rotate90;
	QPushButton *rotate180;
	QPushButton *flipVerticalButton;
	QPushButton *flipHorizontalButton;

	//action in cutWidget
	QGroupBox *cutButtonBox;
	QPushButton *cutRectButton;
	QPushButton *cutRoundButton;
	QPushButton *cutPolygonButton;
	QPushButton *cutPolygonOkButton;
	QGroupBox *imgBox;

	//action in lightWidget
	QGroupBox *lightGroupBox;
	QSlider *lightSlider;
	QLineEdit *lightLineEdit;
	QPushButton *lightOkButton;

	//action in saturationWidget
	QGroupBox *saturationGroupBox;
	QSlider *saturationSlider;
	QLineEdit *saturationLineEdit;
	QPushButton *saturationOkButton;

	//action in toneWidget
	QGroupBox *toneGroupBox;
	QSlider *toneSlider;
	QLineEdit *toneLineEdit;
	QPushButton *toneOkButton;

	//action in linearWidget
	QGroupBox *linearTransGroupBox;
	QLabel *gradientLabel;
	QLineEdit *gradientLineEdit;
	QLabel *biasLabel;
	QLineEdit *biasLineEdit;
	QPushButton *linearTransOkButton;

	//action in piecewiseWidget
	QGroupBox *piecewiseGroupBox;
	QLabel *xRangeLabel;
	QLineEdit *xRangeLineEdit;
	QLabel *gradientLabelPieceWise;
	QLineEdit *gradientLineEditPieceWise;
	QLabel *biasLabelPieceWise;
	QLineEdit *biasLineEditPieceWise;
	QPushButton *pieceWiseTransOkButton;

	//ACTION IN nonlinearWidget
	QGroupBox *nonlinearGroupBox;
	QLabel *aLabel;
	QLabel *bLabel;
	QLabel *cLabel;
	QLabel *gamaLabel;
	QLineEdit *aLineEdit;
	QLineEdit *bLineEdit;
	QLineEdit *cLineEdit;
	QLineEdit *gamaLineEdit;
	QPushButton *nonLinearTransExpButton;
	QPushButton *nonLinearTransLogButton;
	QPushButton *nonLinearTransGamaButton;


	//action in histEquWidget
	QGroupBox *histEquGroupBox;
	QPushButton *viewHistEquButton;
	QPushButton *histEquOkButton;
	QPushButton *viewAfterHistEquButton;

	//action in histSpecWidget
	QGroupBox *histSpecGroupBox;
	QPushButton *histSpecSMLButton;
	QPushButton *histSpecSelectImgButton;
	QPushButton *histSpecGMLButton;
	QPushButton *histSpecViewHistButton;
	QPushButton *histSpecViewAfterHistButton;

	//action in medianFilterWidget
	QGroupBox *medianFilterGroupBox;
	QLabel *medianFilterTemplateSizeLabel;
	QLineEdit *medianFilterTemplateSizeLineEdit;
	QPushButton *medianFilterTemplateShapeButton;
	QPushButton *medianFilterOkButton;

	//action in gaussianBlurWidget
	QGroupBox *gaussianBlurGroupBox;
	QLabel *gaussianBlurRadiusLabel;
	QLineEdit *gaussianBlurRadiusLineEdit;
	QPushButton *gaussianBlurOkButton;
	QLabel *gaussianBlurTemplateSizeLabel;
	QLineEdit *gaussianBlurTemplateSizeLineEdit;

	//action in sharpenWidget
	QGroupBox *sharpenGroupBox;
	QLabel *sharpenThresholdLabel;
	QLineEdit *sharpenThresholeLineEdit;
	QLabel *sharpenIncrementalLabel;
	QLineEdit *sharpenIncrementalLineEdit;
	QPushButton *sharpenRobertsButton;
	QPushButton *sharpenPrewittButton;
	QPushButton *sharpenSobelButton;
	QPushButton *sharpenLaplaceButton;

	//action in filterwidget
	QGroupBox *filterGroupBox;
	QPushButton *lomoFilterButton;
	QPushButton *colorReliefFilterButton;
	QPushButton *pencilDrawingFilterButton;
	QPushButton *latticeFilterButton;


	Rotation rotation;
	CutImage cutImage;
	Hsi hsi;
	ImageEnhancement imageEnhancement;
	SpatialFilter spatialFilter;
	Filter filter;

private slots:
	//旋转
	void clickRotationOk();
	void clickFlipHorizontal();
	void clickFlipVertical();
	void clickRotate90();
	void clickRotate180();

	//裁剪
	void clickCutRect();
	void clickCutRound();
	void clickCutPolygon();
	void clickCutPolygonOk();
	//亮度，饱和度，色调
	void lightSliderValueChanged();
	void saturationSliderValueChanged();
	void toneSliderValueChanged();
	void clickLightOkButton();
	void clickSaturationOkButton();
	void clickToneOkButton();

	//图像增强
	void clickLinearTransOkButton();
	void clickPieceWiseTransOkButton();
	void clickNonLinearTransExpButton();
	void clickNonLinearTransLogButton();
	void clickNonLinearTransGamaButton();
	void clickHistEquOkButton();
	void clickHistSpecSMLButton();
	void clickViewHistEquButton();
	void clickViewAfterHistEquButton();
	void clickHistSpecSelectImgButton();
	void clickHistSpecViewHistButton();
	void clickHistSpecGMLButton();
	void clickHistSpecViewAfterHistButton();
	void clickMedianFilterTemplateShapeButton();
	void clickMedianFilterOkButton();
	void clickGaussianBlurOkButton();
	void clickSharpenRobertsButton();
	void clickSharpenPrewittButton();
	void clickSharpenSobelButton();
	void clickSharpenLaplaceButton();
	void clickLomoFilterButton();
	void clickColorReliefFilterButton();
	void clickPencilDrawingFilterButton();
	void clickLatticeFilterButton();
};

#endif