#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_addSystemDialog = new CAddSystemDialog(this);
	m_addStationDialog = new CAddStationDialog(m_addSystemDialog, this);

	setWindowTitle("Elite Dangerous Trade Helper");
	ui->widget->setTitle("System");
	ui->widget_2->setTitle("Station");
	ui->widget_2->setParentFilterName("system_id");
	ui->widget_3->setTitle("Commodity");
	ui->widget_3->showClearButton();

	ui->widget_3->setParentFilterName("station_id");

	m_model = nullptr;

	m_systemName = "";
	m_planetName = "";
	m_commodityName = "";

	readSettings();
	initialize();

	ui->widget->setTable("Systems");
	ui->widget_2->setTable("Stations");
	ui->widget_3->setTable("GoodNames");

	connect(ui->widget, SIGNAL(textChanged(QString)), this, SLOT(onSystemNameChanged(QString)));
	connect(ui->widget_2, SIGNAL(textChanged(QString)), this, SLOT(onPlanetNameChanged(QString)));
	connect(ui->widget_3, SIGNAL(textChanged(QString)), this, SLOT(onCommodityNameChanged(QString)));

	connect(ui->widget, SIGNAL(listChanged(QVector<SItem>)), this, SLOT(onSystemsListChanged(QVector<SItem>)));
	connect(ui->clearToolButton, SIGNAL(clicked()), this, SLOT(clearFilter()));

	connect(ui->widget, SIGNAL(addButtonClicked(QString)), this, SLOT(addSystemName(QString)));
	connect(ui->widget_2, SIGNAL(addButtonClicked(QString)), this, SLOT(addStation(QString)));
}

MainWindow::~MainWindow()
{
	if (m_model) delete m_model;
	delete ui;
}

/*!
   \brief MainWindow::initialize
   Create database connetion. Fiil table.
 */

void MainWindow::initialize()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	QString  dbFileName(m_dbFile);
	m_db.setDatabaseName(dbFileName);

	QFileInfo fi(dbFileName);

	if (!fi.exists())
	{
		qDebug() << "No file";
		return;
	}

	if (!m_db.open())
	{
		qDebug() << m_db.lastError().text();
		return;
	}

	m_model = new QSqlQueryModel(ui->tableView);
	refreshTable(m_planetName, m_planetName, m_commodityName);
}

void MainWindow::refreshTable(const QString& system, const QString& planet, const QString& commodity)
{
	QStringList filter;

	qDebug() << "MainWindow::refreshTable"
			 << "S:" << system
			 << "P:" << planet
			 << "C:" << commodity;

	if (system.length()+planet.length()+commodity.length() != 0)
	{
		if (!system.isEmpty()) filter.append(QString("UPPER(system) LIKE '%%1%'").arg(system));
		if (!planet.isEmpty()) filter.append(QString("UPPER(station) LIKE '%%1%'").arg(planet));
		if (!commodity.isEmpty()) filter.append(QString("UPPER(name) LIKE '%%1%'").arg(commodity));
	}

	QString condition = (filter.isEmpty() ? "" : " WHERE " + filter.join(" AND "));

	QSqlQuery query("SELECT * FROM GoodsInfoGrouped" + condition);
	query.exec();
	if (!query.isActive())
	{
		qDebug() << query.lastError().text();
		return;
	}

	ui->tableView->setModel(m_model);
	m_model->setQuery(query);
	ui->tableView->resizeColumnsToContents();
}

/*!
   \brief MainWindow::closeEvent
   \param event
   Save window state on closing application.
 */

void MainWindow::closeEvent(QCloseEvent* event)
{
	QSettings settings("ru.glider", "EliteDangerousTradeHelper");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());
	QMainWindow::closeEvent(event);
}

/*!
   \brief MainWindow::restoreWindowState
   Read and restore window state.
 */

void MainWindow::readSettings()
{
	QSettings settings("ru.glider", "EliteDangerousTradeHelper");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());

	m_dbFile = settings.value("dataBase").toString();
	if (m_dbFile.isEmpty()) m_dbFile = "db\\tradeDB.sqlite";
}

void MainWindow::clearFilter()
{
	m_systemName = "";
	m_planetName = "";

	ui->widget->clearFilter();
	ui->widget_2->clearFilter();

	ui->widget_2->setParentFilterValue("");

	refreshTable(m_systemName, m_planetName, m_commodityName);
}

/*!
   \brief MainWindow::onSystemNameChanged
   \param systemName
   Apply filter after changing star system name.
 */

void MainWindow::onSystemNameChanged(QString systemName)
{
	if (systemName.isEmpty()) ui->widget_2->setParentFilterValue("");
	m_systemName = systemName;
	refreshTable(m_systemName, m_planetName, m_commodityName);
}

/*!
   \brief MainWindow::onPlanetNameChanged
   \param planetName
   Apply filter after changing planet name.
 */

void MainWindow::onPlanetNameChanged(QString planetName)
{
	m_planetName = planetName;
	refreshTable(m_systemName, m_planetName, m_commodityName);
}

/*!
   \brief MainWindow::onCommodityNameChanged
   \param commodityName
   Apply filter after changing commodity name.
 */

void MainWindow::onCommodityNameChanged(QString commodityName)
{
	m_commodityName = commodityName;
	refreshTable(m_systemName, m_planetName, m_commodityName);
}

void MainWindow::onSystemsListChanged(QVector<SItem> items)
{
	qDebug() << "MainWindow::onSystemsListChanged" << items.length();

	m_filterItems.clear();

//	if (!m_systemName.isEmpty())
	{
		for (QVector<SItem>::iterator it=items.begin(); it != items.end(); it++)
		{
			m_filterItems.push_back(QString::number(it->id));
		}
	}

	qDebug() << "Filter:" << m_filterItems.join(", ");

	ui->widget_2->setParentFilterValue(m_filterItems.join(", "));
}

void MainWindow::onStationsListChanged(QVector<SItem> items)
{
	qDebug() << "MainWindow::onStationsListChanged";

	m_filterItems.clear();

	if (!m_systemName.isEmpty())
	{
		for (QVector<SItem>::iterator it=items.begin(); it != items.end(); it++)
		{
			m_filterItems.push_back(QString::number(it->id));
		}
	}

	qDebug() << "Filter:" << m_filterItems.join(", ");

	ui->widget_3->setParentFilterValue(m_filterItems.join(", "));
}

void MainWindow::addSystemName(QString text)
{
	m_addSystemDialog->setup(text);
	if (m_addSystemDialog->exec() == QDialog::Accepted)
	{
		// done
		clearFilter();
	}
}

void MainWindow::addStation(QString text)
{
	m_addStationDialog->setup(m_systemName);
	if (m_addStationDialog->exec() == QDialog::Accepted)
	{
		// done
		clearFilter();
	}
}
