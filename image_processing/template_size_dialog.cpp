#include "template_size_dialog.h"
#include "main_window.h"
TemplateSizeDialog::TemplateSizeDialog(int template_size, Main_window *parent)
	:QDialog(parent)
{
	this->parent = parent;
	selectAll = new QCheckBox(tr("select all"), this);
	resize((template_size + 1)* 50 + 50, (template_size + 2) * 50 + 100);

	selectAll->move(20, 20);

	QPushButton *ok = new QPushButton(tr("Ok"), this);
	ok->move((template_size + 1) * 50 - 50, (template_size + 2) * 50 + 50);
	setWindowTitle(tr("select template shape"));
	this->template_size = template_size;

	is_selected = new bool*[template_size];
	for (int i = 0; i < template_size; i++)
	{
		is_selected[i] = new bool[template_size];
		for (int j = 0; j < template_size; j++)
		{
			is_selected[i][j] = true;
		}
	}
	selectAll->setCheckState(Qt::Checked);
	connect(selectAll, &QCheckBox::stateChanged, this, &TemplateSizeDialog::selectAllStateChanged);
	connect(ok, &QPushButton::clicked, this, &TemplateSizeDialog::clickOk);
	parent->medianTemplateSizeLast = template_size;
}

TemplateSizeDialog::~TemplateSizeDialog()
{


}

void TemplateSizeDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);

	for (int i = 0; i <= template_size; i++)
	{
		painter->drawLine(50, 100 + i * 50, 50 + template_size * 50, 100 + i * 50);
		painter->drawLine(50 + 50 * i, 100, 50 + 50 * i, 100 + template_size * 50);
	}

	for (int i = 0; i < template_size; i++)
	{
		for (int j = 0; j < template_size; j++)
		{
			if (is_selected[i][j] == false)
			{
				painter->setBrush(Qt::red);
			}
			else
			{
				painter->setBrush(Qt::gray);
			}
			painter->drawRect(50 * j + 50, 50 * i + 100,  50,  50);
		}
	}
}

void TemplateSizeDialog::mousePressEvent(QMouseEvent *event)
{
	QPoint point = event->pos();
	if (point.x() <= 50 || point.y() <= 100 || point.x() >= 50 + 50 * template_size || point.y() >= 100 + 50 * template_size)
	{
		return;
	}

	int i = (point.y() - 100) / 50;
	int j = (point.x() - 50) / 50;
	is_selected[i][j] = !is_selected[i][j];
	update();

}

void TemplateSizeDialog::selectAllStateChanged()
{
	bool ok = selectAll->checkState() == Qt::Checked;

	for (int i = 0; i < template_size; i++)
	{
		for (int j = 0; j < template_size; j++)
		{
			is_selected[i][j] = ok;
		}
	}

	update();
}

void TemplateSizeDialog::clickOk()
{
	parent->medianFilterTemplateShape = new bool*[template_size];
	for (int i = 0; i < template_size; i++)
	{
		parent->medianFilterTemplateShape[i] = new bool[template_size];
		for (int j = 0; j < template_size; j++)
		{
			parent->medianFilterTemplateShape[i][j] = is_selected[i][j];
		}
	}
	close();
}
