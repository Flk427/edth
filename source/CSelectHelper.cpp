#include "CSelectHelper.h"
#include "ui_CSelectHelper.h"

CSelectHelper::CSelectHelper(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CSelectHelper)
{
	ui->setupUi(this);
	connect(ui->comboBox, SIGNAL(editTextChanged(QString)), this, SLOT(onLabelTextChanged(QString)));
}

CSelectHelper::~CSelectHelper()
{
	delete ui;
}

void CSelectHelper::setTitle(const QString& text)
{
	ui->label->setText(text);
}

QString CSelectHelper::getText()
{
	return ui->label->text();
}

void CSelectHelper::onLabelTextChanged(QString text)
{
	emit textChanged(text);
}
