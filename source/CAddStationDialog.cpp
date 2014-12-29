#include "CAddStationDialog.h"
#include "ui_CAddStationDialog.h"

#include <QSqlQuery>
#include <QDebug>

CAddStationDialog::CAddStationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CAddStationDialog)
{
	ui->setupUi(this);

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAcceptClicked()));
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged()));

	m_mode = modeEdit;
}

void CAddStationDialog::setup(PSSTATE pState, QString newName)
{
	m_pState = pState;
	m_newName = newName;
	m_oldName = m_pState->m_stationName;

	ui->lineEdit->setText(newName);
	ui->busyLabel->hide();

//	QString queryText(QString("SELECT id FROM stations WHERE UPPER(name)=UPPER('%1') AND system_id=%2")
//					  .arg(m_pState->m_stationName)
//					  .arg(m_pState->m_systemId));

	QString queryText(QString("SELECT id FROM stations WHERE id=%1 AND UPPER(name)=UPPER('%2')")
					  .arg(m_pState->m_stationId)
					  .arg(m_newName));

	qDebug() << queryText;

	QSqlQuery query;
	query.exec(queryText);
	if (query.next() && m_pState->m_stationSelected)
	{
		m_mode = modeEdit;
		m_id = query.value("id").toInt();
		ui->label->setText("Edit station at " + m_pState->m_selectedSystemName);
		qDebug() << "CAddStationDialog in edit mode";
	}
	else
	{
		m_mode = modeAdd;
		ui->label->setText("Add new station at " + m_pState->m_selectedSystemName);
		qDebug() << "CAddStationDialog in add mode";
	}
}

CAddStationDialog::~CAddStationDialog()
{
	delete ui;
}

void CAddStationDialog::onAcceptClicked()
{
	if (ui->lineEdit->text().isEmpty())
	{
		ui->busyLabel->setText("*) Name is empty");
		ui->busyLabel->show();
		return;
	}

	// Check unique
	QString queryText(QString("SELECT id FROM stations WHERE UPPER(name)=UPPER('%1')").arg(ui->lineEdit->text()));
	QSqlQuery query;
	query.exec(queryText);
	if (query.next())
	{
		if (m_mode == modeEdit && m_oldName == ui->lineEdit->text())
		{
			ui->busyLabel->setText("*) Name are same");
		}
		else
		{
			ui->busyLabel->setText("*) Name already busy");
		}
		ui->busyLabel->show();
		qDebug() << "Name is not unique.";
		return;
	}

	if (m_mode == modeAdd)
	{
		queryText = QString("INSERT INTO stations (name, system_id, government_id) VALUES ('%1', %2, 0)").arg(ui->lineEdit->text().arg(m_pState->m_systemId));
		query.exec(queryText);
	}
	else
	{
		queryText = QString("UPDATE stations SET name='%1' WHERE id=%2").arg(ui->lineEdit->text()).arg(m_id);
		query.exec(queryText);
	}
	accept();
}

void CAddStationDialog::onTextChanged()
{
	ui->busyLabel->hide();
}
