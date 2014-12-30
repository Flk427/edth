#include "CAddSystemDialog.h"
#include "ui_CAddSystemDialog.h"

#include <QSqlQuery>
#include <QDebug>

CAddSystemDialog::CAddSystemDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CAddSystemDialog)
{
	ui->setupUi(this);
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAcceptClicked()));
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged()));

	m_mode = modeEdit;
}

CAddSystemDialog::~CAddSystemDialog()
{
	delete ui;
}

void CAddSystemDialog::setup(QString name)
{
	m_oldName = name;

	ui->lineEdit->setText(name);
	ui->busyLabel->hide();

	QString queryText(QString("SELECT id FROM systems WHERE name='%1'").arg(name));

	QSqlQuery query;
	query.exec(queryText);
	if (query.next())
	{
		m_mode = modeEdit;
		m_id = query.value("id").toInt();
		ui->label->setText("Edit system");
		qDebug() << "CAddSystemDialog in edit mode";
	}
	else
	{
		m_mode = modeAdd;
		ui->label->setText("Add new system");
		qDebug() << "CAddSystemDialog in add mode";
	}
}

void CAddSystemDialog::onAcceptClicked()
{
	if (ui->lineEdit->text().isEmpty())
	{
		ui->busyLabel->setText("*) Name is empty");
		ui->busyLabel->show();
		return;
	}

	// Check unique
	QString queryText(QString("SELECT id FROM systems WHERE UPPER(name)=UPPER('%1')").arg(ui->lineEdit->text()));
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
		queryText = QString("INSERT INTO systems (name, economy_id, government_id, population) VALUES ('%1', 0, 0, 0)").arg(ui->lineEdit->text());
		query.exec(queryText);
	}
	else
	{
		queryText = QString("UPDATE systems SET name='%1' WHERE id=%2").arg(ui->lineEdit->text()).arg(m_id);
		query.exec(queryText);
	}
	accept();
}

void CAddSystemDialog::onTextChanged()
{
	ui->busyLabel->hide();
}
