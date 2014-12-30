#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <QSettings>
#include <QPoint>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	state.m_systemSelected = false;
	state.m_systemId = -1;

	state.m_stationSelected = false;
	state.m_stationId = -1;

	state.m_commoditySelected = false;
	state.m_commodityId = -1;

	activatePriceButton();

	m_addSystemDialog = new CAddSystemDialog(this);
	m_addStationDialog = new CAddStationDialog(this);
	m_addPriceDialog = new CAddPriceDialog(this);

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
	connect(ui->widget_2, SIGNAL(listChanged(QVector<SItem>)), this, SLOT(onStationsListChanged(QVector<SItem>)));
	connect(ui->widget_3, SIGNAL(listChanged(QVector<SItem>)), this, SLOT(onCommodityesListChanged(QVector<SItem>)));
	connect(ui->clearToolButton, SIGNAL(clicked()), this, SLOT(clearFilter()));
	connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(clearAllFilters()));

	connect(ui->widget, SIGNAL(addButtonClicked(QString)), this, SLOT(addSystemName(QString)));
	connect(ui->widget_2, SIGNAL(addButtonClicked(QString)), this, SLOT(addStation(QString)));

	connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(onSetPriceClicked()));
	connect(ui->widget_3, SIGNAL(enterPressed()), this, SLOT(onSetPriceClicked()));

	setupStationEditButton();
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

void MainWindow::setupStationEditButton()
{
	ui->widget_2->setEditButtonEnabled(
				state.m_systemSelected // Если выбрана система - можно добавить новую станцию
				|| (ui->widget_2->getText() == state.m_stationName && state.m_stationSelected));
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

void MainWindow::clearAllFilters()
{
	m_systemName = "";
	m_planetName = "";
	m_commodityName = "";

	ui->widget->clearFilter();
	ui->widget_2->clearFilter();
	ui->widget_3->clearFilter();

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

//	if (ui->widget->getText().isEmpty())
//	{
//		ui->widget_2->setParentFilterValue("");
//		return;
//	}

	m_filterItems.clear();

//	if (!m_systemName.isEmpty())
	{
		for (QVector<SItem>::iterator it=items.begin(); it != items.end(); it++)
		{
			m_filterItems.push_back(QString::number(it->id));
		}
	}

	qDebug() << "Filter:" << m_filterItems.join(", ");

	if (m_filterItems.length() == 1)
	{
		state.m_systemSelected = true;
		state.m_systemId = items[0].id;
		state.m_selectedSystemName = items[0].name;
		qDebug() << "MainWindow::onSystemsListChanged: System selected:" << state.m_systemId;
	}
	else
	{
		state.m_systemSelected = false;
		state.m_systemId = -1;
		state.m_selectedSystemName = "";
		qDebug() << "MainWindow::onSystemsListChanged: System not selected";
	}

	setupStationEditButton();

	ui->widget_2->setParentFilterValue(m_filterItems.join(", "));
}

void MainWindow::onStationsListChanged(QVector<SItem> items)
{
	qDebug() << "MainWindow::onStationsListChanged";

	m_filterItems.clear();

//	if (!m_systemName.isEmpty())
	{
		for (QVector<SItem>::iterator it=items.begin(); it != items.end(); it++)
		{
			m_filterItems.push_back(QString::number(it->id));
		}
	}

	qDebug() << "Stations:" << m_filterItems.join(", ");

	if (m_filterItems.length() == 1)
	{
		state.m_stationSelected = true;
		state.m_stationId = items[0].id;
		state.m_stationName = items[0].name;
		qDebug() << "MainWindow::onStationsListChanged: Staion selected:" << state.m_stationId;

		m_planetName = state.m_stationName;
		refreshTable(m_systemName, m_planetName, m_commodityName);
	}
	else
	{
		state.m_stationSelected = false;
		state.m_stationId = -1;
		state.m_stationName = "";
		qDebug() << "MainWindow::onStationsListChanged: Staion not selected";

		m_planetName = "";
		refreshTable(m_systemName, m_planetName, m_commodityName);
	}

	setupStationEditButton();
	activatePriceButton();

//	ui->widget_3->setParentFilterValue(m_filterItems.join(", "));
}

void MainWindow::onCommodityesListChanged(QVector<SItem> items)
{
	qDebug() << "MainWindow::onCommodityesListChanged";

	m_filterItems.clear();

	for (QVector<SItem>::iterator it=items.begin(); it != items.end(); it++)
	{
		m_filterItems.push_back(QString::number(it->id));
	}

	qDebug() << "Commodityes:" << m_filterItems.join(", ");

	if (m_filterItems.length() == 1)
	{
		state.m_commoditySelected = true;
		state.m_commodityId = items[0].id;
		qDebug() << "MainWindow::onCommodityesListChanged: Commodity selected:" << state.m_commodityId;
	}
	else
	{
		state.m_commoditySelected = false;
		state.m_commodityId = -1;
		qDebug() << "MainWindow::onCommodityesListChanged: Commodity not selected";
	}

	activatePriceButton();
}

void MainWindow::addSystemName(QString text)
{
	m_addSystemDialog->setup(text);
//	m_addSystemDialog->setup(m_selectedSystemName);
	if (m_addSystemDialog->exec() == QDialog::Accepted)
	{
		// done
		clearFilter();
	}
}

void MainWindow::addStation(QString text)
{
	m_addStationDialog->setup(&state, ui->widget_2->getText());
	if (m_addStationDialog->exec() == QDialog::Accepted)
	{
		// done
		clearFilter();
	}
}

void MainWindow::onSetPriceClicked()
{
	qDebug() << "Set price for:" << state.m_commodityId << "at:" << state.m_stationId;
	m_addPriceDialog->setup(state.m_stationId, state.m_commodityId);

	const QPoint global = this->mapToGlobal(rect().center());
	m_addPriceDialog->move(global.x() - m_addPriceDialog->width() / 2, global.y() - m_addPriceDialog->height() / 2);

	if (m_addPriceDialog->exec())
	{
		refreshTable(m_systemName, m_planetName, m_commodityName);
	}
	//showSetPriceDialog();
	//	m_stationId
	//	m_commodityId
}

void MainWindow::activatePriceButton()
{
	ui->toolButton->setEnabled(state.m_stationSelected && state.m_commoditySelected);
}
