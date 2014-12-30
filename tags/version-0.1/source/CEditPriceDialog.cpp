#include "CEditPriceDialog.h"
#include "ui_CEditPriceDialog.h"

#include <QSqlQuery>
#include <QDebug>
#include <QKeyEvent>
#include <QDateTime>
#include <QPushButton>

CEditPriceDialog::CEditPriceDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CEditPriceDialog)
{
	ui->setupUi(this);
	ui->lineEdit->installEventFilter(this);
	ui->lineEdit_2->installEventFilter(this);

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onOk()));
}

CEditPriceDialog::~CEditPriceDialog()
{
	delete ui;
}

int CEditPriceDialog::begin(int id)
{
	m_id = id;

	QString queryText = "SELECT si.name AS system, st.name AS station, gg.name AS gname,"
						" gn.name AS commodity, pr.sale_price AS sale, pr.buy_price AS buy"
						" FROM prices AS pr"
						" LEFT JOIN goodnames AS gn ON gn.id=pr.good_id"
						" LEFT JOIN goodgroups AS gg ON gg.id=gn.group_id"
						" LEFT JOIN stations AS st ON st.id=pr.station_id"
						" LEFT JOIN systems AS si ON si.id=st.system_id"
						+QString(" WHERE pr.id=%1").arg(m_id);

	qDebug() << queryText;

	QSqlQuery query;
	query.exec(queryText);
	if (query.next())
	{
		ui->label->setText("System: " + query.value("system").toString()
						   + " Station: " + query.value("station").toString());
		ui->label_4->setText("Group: " + query.value("gname").toString()
						   + " Commodity: " + query.value("commodity").toString());

		ui->lineEdit->setText(query.value("sale").toString());
		ui->lineEdit_2->setText(query.value("buy").toString());

		ui->lineEdit->setFocus();
		ui->lineEdit->selectAll();

		return exec();
	}
	else
	{
		return QDialog::Rejected;
	}
}

bool CEditPriceDialog::eventFilter(QObject* obj, QEvent* event)
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

void CEditPriceDialog::onOk()
{
	bool isInt1;
	bool isInt2;

	m_sell = ui->lineEdit->text().toInt(&isInt1);
	m_buy = ui->lineEdit_2->text().toInt(&isInt2);

	QDateTime time = QDateTime::currentDateTime();

	QString timeStr(
				QString("%1-%2-%3 %4:%5:%6")
				.arg(time.date().year())
				.arg(time.date().month())
				.arg(time.date().day())
				.arg(time.time().hour())
				.arg(time.time().minute())
				.arg(time.time().second()));

	QString queryText = QString("UPDATE prices SET sale_price=%1, buy_price=%2, time='%3'"
								" WHERE id=%4").arg(m_sell).arg(m_buy).arg(timeStr).arg(m_id);

	qDebug() << queryText;

	QSqlQuery query;
	query.exec(queryText);
	accept();
}
