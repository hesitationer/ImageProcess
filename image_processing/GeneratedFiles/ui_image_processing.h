/********************************************************************************
** Form generated from reading UI file 'image_processing.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_PROCESSING_H
#define UI_IMAGE_PROCESSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_image_processingClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *image_processingClass)
    {
        if (image_processingClass->objectName().isEmpty())
            image_processingClass->setObjectName(QStringLiteral("image_processingClass"));
        image_processingClass->resize(600, 400);
        centralWidget = new QWidget(image_processingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        image_processingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(image_processingClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        image_processingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(image_processingClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        image_processingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(image_processingClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        image_processingClass->setStatusBar(statusBar);

        retranslateUi(image_processingClass);

        QMetaObject::connectSlotsByName(image_processingClass);
    } // setupUi

    void retranslateUi(QMainWindow *image_processingClass)
    {
        image_processingClass->setWindowTitle(QApplication::translate("image_processingClass", "image_processing", 0));
    } // retranslateUi

};

namespace Ui {
    class image_processingClass: public Ui_image_processingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_PROCESSING_H
