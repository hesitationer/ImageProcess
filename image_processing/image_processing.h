#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QContextMenuEvent>
#include <QClipboard>
#include <QMessageBox>
#include "ui_image_processing.h"
#include "main_window.h"

class Image_processing : public QMainWindow
{
	Q_OBJECT

public:
	Image_processing(QWidget *parent = 0);
	~Image_processing();

private:
	Ui::image_processingClass ui;

	QMenu *fileMenu;
	QMenu *enhancementMenu;
	QMenu *spatialFilterMenu;
	QMenu *frequencyFilterMenu;
	QToolBar *toolBar;
	QActionGroup *alignmentGroup;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *cutAct;
	QAction *linearTransAct;
	QAction *piecewiseLinearTransAct;
	QAction *nonlinearTransAct;
	QAction *histogramEqualizationAct;
	QAction *histogramSpecificationAct;
	QAction *medianFilterAct;
	QAction *gaussianBlurAct;
	QAction *sharpenAct;
	QAction *frequencySmoothAct;
	QAction *frequencySharpenAct;
	//QLabel *infoLabel;
	Main_window *window;

	//action in toolbar
	QAction *rotationAct;
	QAction *lightAct;
	QAction *saturationAct;
	QAction *toneAct;
	QAction *filterAct;
	void createActions();
	void createMenus();


private slots:
	void open();
	void save();
	void exit();
	void saveAs();
	void rotation();
	void cut();
	void light();
	void saturation();
	void tone();
	void linearTrans();
	void piecewiseLinearTrans();
	void nonlinearTrans();
	void histogramEqualization();
	void histogramSpecification();
	void medianFilter();
	void gaussianBlur();
	void sharpen();
	void frequencySmooth();
	void frequencySharpen();
	void filter();


/*protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif QT_NO_CONTEXTMENU*/
};

#endif // IMAGE_PROCESSING_H
