#include "CAddStationDialog.h"
#include "ui_CAddStationDialog.h"

CAddStationDialog::CAddStationDialog(CAddSystemDialog* addSystemDialog, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CAddStationDialog)
{
	m_addSystemDialog = addSystemDialog;

	ui->setupUi(this);

	ui->widget->showClearButton();
	ui->widget->setTitle("System");
	ui->widget->setTable("Systems");
//	connect(ui->widget, SIGNAL(textChanged(QString)), this, SLOT(onSystemNameChanged(QString)));
	connect(ui->widget, SIGNAL(addButtonClicked(QString)), this, SLOT(addSystemName(QString)));
}

void CAddStationDialog::setup(QString stationName)
{
	m_stationName = stationName;
	ui->widget->setFilter(m_stationName);
}

CAddStationDialog::~CAddStationDialog()
{
	delete ui;
}

void CAddStationDialog::addSystemName(QString text)
{
	m_addSystemDialog->setup(text);
	if (m_addSystemDialog->exec() == QDialog::Accepted)
	{
		// done
//		clearFilter();
	}
}
