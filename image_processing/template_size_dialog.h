#ifndef TEMPLATE_SIZE_DIALOG_H
#define TEMPLATE_SIZE_DIALOG_H
#include <QDialog>
#include <QCheckBox>
#include <QVector>
class Main_window;
class TemplateSizeDialog : public QDialog
{
	
public:
	TemplateSizeDialog (int template_size, Main_window *parent);
	~TemplateSizeDialog();
	Main_window *parent;
	int template_size;
	bool **is_selected;
	QCheckBox *selectAll;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:

private slots:
	void selectAllStateChanged();
	void clickOk();
};


#endif