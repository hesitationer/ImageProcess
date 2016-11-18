#include <QVBoxLayout>
#include <QfileDialog>
#include "image_processing.h"

Image_processing::Image_processing(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


	window = new Main_window;
	//window->resize(800, 600);

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);
	layout->addWidget(topFiller);
	layout->addWidget(window);
	layout->addWidget(bottomFiller);
	widget->setLayout(layout);

	createActions();
	createMenus();

	QString message = tr("A context menu is available by right-click.");
	statusBar()->showMessage(message);

	setWindowTitle(tr("image processing"));
	setMinimumSize(200, 160);
	resize(1280, 960);

}

Image_processing::~Image_processing()
{

}

void Image_processing::createActions()
{
	

	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcut(QKeySequence::Open);
	openAct->setStatusTip(tr("open a file"));
	connect(openAct, &QAction::triggered, this, &Image_processing::open);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcut(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the file"));
	connect(saveAct, &QAction::triggered, this, &Image_processing::save);

	const QIcon cutIcon = QIcon::fromTheme("document-new", QIcon(":/Images/Resources/cut.png"));
	cutAct = new QAction(cutIcon ,tr("&Cut"), this);
	cutAct->setStatusTip(tr("Cut the image"));
	connect(cutAct, &QAction::triggered, this, &Image_processing::cut);

	exitAct = new QAction(tr("&Exit"), this);
	exitAct->setStatusTip(tr("exit "));
	exitAct->setShortcut(QKeySequence::Quit);
	connect(exitAct, &QAction::triggered, this, &Image_processing::exit);

	saveAsAct = new QAction(tr("&Save as "), this);
	saveAsAct->setShortcut(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("save as "));
	connect(saveAsAct, &QAction::triggered, this, &Image_processing::saveAs);

	//action in toolbar
	const QIcon rotationIcon = QIcon::fromTheme("document-new", QIcon(":/Images/Resources/rotation.png"));
	rotationAct = new QAction(rotationIcon, tr("&rotation"), this);
	rotationAct->setStatusTip(tr("rotation of the image"));
	connect(rotationAct, &QAction::triggered, this, &Image_processing::rotation);

	const QIcon lightIcon = QIcon::fromTheme("document-new", QIcon(":/image_processing/Resources/brightness.png"));
	lightAct = new QAction(lightIcon, tr("&Light"), this);
	lightAct->setStatusTip(tr("change the light"));
	connect(lightAct, &QAction::triggered, this, &Image_processing::light);

	const QIcon toneIcon = QIcon::fromTheme("document-new", QIcon(":/image_processing/Resources/tone.PNG"));
	toneAct = new QAction(toneIcon, tr("&Tone"), this);
	toneAct->setStatusTip(tr("change the tone"));
	connect(toneAct, &QAction::triggered, this, &Image_processing::tone);

	const QIcon saturationIcon = QIcon::fromTheme("document-new", QIcon(":/image_processing/Resources/saturation.PNG"));
	saturationAct = new QAction(saturationIcon, tr("&Saturation"), this);
	saturationAct->setStatusTip(tr("change the saturation"));
	connect(saturationAct, &QAction::triggered, this, &Image_processing::saturation);

	linearTransAct = new QAction(tr("Linear Transformation"), this);
	connect(linearTransAct, &QAction::triggered, this, &Image_processing::linearTrans);

	piecewiseLinearTransAct = new QAction(tr("Piecewise Linear Transformation"), this);
	connect(piecewiseLinearTransAct, &QAction::triggered, this, &Image_processing::piecewiseLinearTrans);

	nonlinearTransAct = new QAction(tr("Nonlinear Transformation"), this);
	connect(nonlinearTransAct, &QAction::triggered, this, &Image_processing::nonlinearTrans);

	histogramEqualizationAct = new QAction(tr("Histogram Equalization"), this);
	connect(histogramEqualizationAct, &QAction::triggered, this, &Image_processing::histogramEqualization);

	histogramSpecificationAct = new QAction(tr("Histogram Specification"), this);
	connect(histogramSpecificationAct, &QAction::triggered, this, &Image_processing::histogramSpecification);

	medianFilterAct = new QAction(tr("Median Filter"), this);
	connect(medianFilterAct, &QAction::triggered, this, &Image_processing::medianFilter);

	gaussianBlurAct = new QAction(tr("Gaussian Blur"), this);
	connect(gaussianBlurAct, &QAction::triggered, this, &Image_processing::gaussianBlur);

	sharpenAct = new QAction(tr("Sharpen"), this);
	connect(sharpenAct, &QAction::triggered, this, &Image_processing::sharpen);

	frequencySharpenAct = new QAction(tr("Sharpen"), this);
	connect(frequencySharpenAct, &QAction::triggered, this, &Image_processing::frequencySharpen);

	frequencySmoothAct = new QAction(tr("Smooth"), this);
	connect(frequencySmoothAct, &QAction::triggered, this, &Image_processing::frequencySmooth);

	const QIcon filterIcon = QIcon::fromTheme("document-new", QIcon(":/Images/Resources/filter.PNG"));
	filterAct = new QAction(filterIcon, tr("&Filter"), this);
	connect(filterAct, &QAction::triggered, this, &Image_processing::filter);
 }

void Image_processing::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	enhancementMenu = menuBar()->addMenu(tr("&Enhancement"));
	enhancementMenu->addAction(linearTransAct);
	enhancementMenu->addAction(piecewiseLinearTransAct);
	enhancementMenu->addAction(nonlinearTransAct);
	enhancementMenu->addAction(histogramEqualizationAct);
	enhancementMenu->addAction(histogramSpecificationAct);

	spatialFilterMenu = menuBar()->addMenu(tr("Spatial Filter"));
	spatialFilterMenu->addAction(medianFilterAct);
	spatialFilterMenu->addAction(gaussianBlurAct);
	spatialFilterMenu->addAction(sharpenAct);

	frequencyFilterMenu = menuBar()->addMenu(tr("Frequency Filter"));
	frequencyFilterMenu->addAction(frequencySmoothAct);
	frequencyFilterMenu->addAction(frequencySharpenAct);

	toolBar = addToolBar(tr("&Rotation"));
	toolBar->setAllowedAreas(Qt::LeftToolBarArea);
	toolBar->addAction(rotationAct);
	toolBar->addAction(cutAct);
	toolBar->addAction(lightAct);
	toolBar->addAction(saturationAct);
	toolBar->addAction(toneAct);
	toolBar->addAction(filterAct);

}


void Image_processing::open()
{
	 window->path = QFileDialog::getOpenFileName(
		this,
		"Select one or more files to open",
		"",
		"Images (*.png *.xpm *.jpg)");

	if (!window->path.isEmpty() && !window->path.isNull()) {
		statusBar()->showMessage(window->path);
		window->first = true;
		window->loadImages();
		statusBar()->showMessage(tr("show image"));
	}
	

}
void Image_processing::save()
{
	window->saveImages(window->path.toStdString(), window->img);
}
void Image_processing::cut()
{
	window->showCutWidget();
}
/*void Image_processing::copy()
{
	if (!window->checkImage())
	{
		return;
	}
	QClipboard *board = QApplication::clipboard();
	cvtColor(window->img, window->img, CV_BGR2RGB);
	QImage imdisplay((uchar*)window->img.data, window->img.cols, window->img.rows, window->img.step, QImage::Format_RGB888);
	QPixmap pix = QPixmap::fromImage(imdisplay);
	board->setPixmap(pix, QClipboard::Clipboard);
	return;
}*/
/*void Image_processing::paste()
{
	QClipboard *board = QApplication::clipboard();
	QPixmap pix = board->pixmap();
	if (pix.isNull())
	{
		QMessageBox::information(this,
			tr("tips"), tr("there  is no image that can be pasted"));
		return;
	}
	QImage image = pix.toImage();
	Mat temp(image.height(), image.width(), CV_8UC1, const_cast<uchar*>(image.bits()), static_cast<size_t>(image.bytesPerLine()));
	window->oldImg = temp;
	window->first = true;
	window->drawImages(window->oldImg);
}*/

void Image_processing::exit()
{
	close();
}

void Image_processing::saveAs()
{
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("save as"),
		tr("undefine.jpg"),
		tr("Images (*.png *.bmp *.jpg)"),
		&selectedFilter);
	if (!fileName.isEmpty() && !fileName.isNull())
	{
		statusBar()->showMessage(fileName);
		window->saveImages(fileName.toStdString(), window->img);

	}
}

void Image_processing::rotation()
{
	window->showRotation();
}

void Image_processing::light()
{
	window->showLight();
}

void Image_processing::saturation()
{
	window->showSaturation();
}

void Image_processing::tone()
{
	window->showTone();
}

/*#ifndef QT_NO_CONTEXTMENU
void Image_processing::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);
	menu.exec(event->globalPos());

}
#endif */

void Image_processing::linearTrans()
{
	window->showLinearTrans();
}

void Image_processing::piecewiseLinearTrans()
{
	window->showPieceWiseLinearTrans();
}

void Image_processing::nonlinearTrans()
{
	window->showNonlinearTrans();
}

void Image_processing::histogramEqualization()
{
	window->showHistEquTrans();
}

void Image_processing::histogramSpecification()
{
	window->showHistSpecTrans();
}

void Image_processing::medianFilter()
{
	window->showMedianFilter();
}

void Image_processing::gaussianBlur()
{
	window->showGaussianBlur();
}

void Image_processing::sharpen()
{
	window->showSharpen();
}

void Image_processing::frequencySharpen()
{

}

void Image_processing::frequencySmooth()
{

}

void Image_processing::filter()
{
	window->showFilter();
}