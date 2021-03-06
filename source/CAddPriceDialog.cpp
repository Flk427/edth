#include "CAddPriceDialog.h"
#include "ui_CAddPriceDialog.h"

#include <QSqlQuery>
#include <QPushButton>
#include <QDateTime>
#include <QKeyEvent>
#include <QDebug>

CAddPriceDialog::CAddPriceDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CAddPriceDialog)
{
	ui->setupUi(this);
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAcceptClicked()));
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(validateData()));
	connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(validateData()));

	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	ui->lineEdit->installEventFilter(this);
	ui->lineEdit_2->installEventFilter(this);
}

CAddPriceDialog::~CAddPriceDialog()
{
	delete ui;
}

void CAddPriceDialog::setup(int station, int commodity)
{
	m_station = station;
	m_commodity = commodity;

	ui->lineEdit->setText("");
	ui->lineEdit->setFocus();
	ui->lineEdit_2->setText("");

	QString queryText(QString("SELECT UPPER(name) AS name FROM stations WHERE id=%1").arg(m_station));
	QSqlQuery query;
	query.exec(queryText);
	if (query.next())
	{
		ui->label->setText("Station: " + query.value("name").toString());
	}

	queryText = QString("SELECT UPPER(name) AS name FROM GoodNames WHERE id=%1").arg(m_commodity);
	query.exec(queryText);

	if (query.next())
	{
		ui->label_4->setText("Commodity: " + query.value("name").toString());
	}
}

bool CAddPriceDialog::eventFilter(QObject* obj, QEvent *event)
{
	if (obj == ui->lineEdit)
		{
			if (event->type() == QEvent::KeyPress)
			{
				QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
				if(keyEvent->key() == Qt::Key_Down)
				{
					qDebug() << "lineEdit -> Qt::Key_Down";
					ui->lineEdit_2->setFocus();
					ui->lineEdit_2->selectAll();
					return true;
				}
			}
			return false;
		}
	if (obj == ui->lineEdit_2)
		{
			if (event->type() == QEvent::KeyPress)
			{
				QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
				if (keyEvent->key() == Qt::Key_Up)
				{
					 qDebug() << "lineEdit -> Qt::Key_Up";
					 ui->lineEdit->setFocus();
					 ui->lineEdit->selectAll();
					 return true;
				}
			}
			return false;
		}
		return QDialog::eventFilter(obj, event);
}

void CAddPriceDialog::onAcceptClicked()
{
	QDateTime time = QDateTime::currentDateTime();

	QString timeStr(
				QString("%1-%2-%3 %4:%5:%6")
				.arg(time.date().year())
				.arg(time.date().month())
				.arg(time.date().day())
				.arg(time.time().hour())
				.arg(time.time().minute())
				.arg(time.time().second()));

	QString queryText;

	if (ui->lineEdit_2->text().isEmpty())
	{
		queryText = QString("INSERT INTO prices (good_id, station_id, time, sale_price) "
							+QString(" VALUES (%1, %2, '%3', %4)")
							.arg(m_commodity)
							.arg(m_station)
							.arg(timeStr)
							.arg(m_sell));
	}
	else
	{
		queryText = QString("INSERT INTO prices (good_id, station_id, time, sale_price, buy_price) "
							+QString(" VALUES (%1, %2, '%3', %4, %5)")
							.arg(m_commodity)
							.arg(m_station)
							.arg(timeStr)
							.arg(m_sell)
							.arg(m_buy));
	}
	QSqlQuery query;
	query.exec(queryText);

	accept();
}

void CAddPriceDialog::validateData()
{
	bool isInt1;
	bool isInt2;

	m_sell = ui->lineEdit->text().toInt(&isInt1);
	m_buy = ui->lineEdit_2->text().toInt(&isInt2);

	if (!isInt1)
	{
		ui->label_2->setText("Sell*");
	}
	else
	{
		ui->label_2->setText("Sell");
	}

	if (!ui->lineEdit_2->text().isEmpty() && !isInt2)
	{
		ui->label_3->setText("Buy*");
	}
	else
	{
		ui->label_3->setText("Buy");
	}

	if (!isInt1 || !isInt2 && !ui->lineEdit_2->text().isEmpty())
	{
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	}
	else
	{
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
	}
}
