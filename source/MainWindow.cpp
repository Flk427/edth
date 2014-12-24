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
	setWindowTitle("Elite Dangerous Trade Helper");
	ui->widget->setTitle("System");
	ui->widget_2->setTitle("Planet");
	ui->widget_3->setTitle("Commodity");

	m_model = nullptr;

	m_systemName = "";
	m_planetName = "";
	m_commodityName = "";

	restoreWindowState();
	initialize();

	connect(ui->widget, SIGNAL(textChanged(QString)), this, SLOT(onSystemNameChanged(QString)));
	connect(ui->widget_2, SIGNAL(textChanged(QString)), this, SLOT(onPlanetNameChanged(QString)));
	connect(ui->widget_3, SIGNAL(textChanged(QString)), this, SLOT(onCommodityNameChanged(QString)));
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
	QString  dbFileName("db\\tradeDB.sqlite");
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

//	qDebug() << commodity;

	if (system.length()+planet.length()+commodity.length() != 0)
	{
//		if (!system.isEmpty()) filter.append(QString("UPPER(system) LIKE '%%1%'").arg(system));
		if (!planet.isEmpty()) filter.append(QString("UPPER(planet) LIKE '%%1%'").arg(planet));
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

void MainWindow::restoreWindowState()
{
	QSettings settings("ru.glider", "EliteDangerousTradeHelper");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());
}

/*!
   \brief MainWindow::onSystemNameChanged
   \param systemName
   Apply filter after changing star system name.
 */

void MainWindow::onSystemNameChanged(QString systemName)
{
	m_systemName = systemName;
	refreshTable(m_planetName, m_planetName, m_commodityName);
}

/*!
   \brief MainWindow::onPlanetNameChanged
   \param planetName
   Apply filter after changing planet name.
 */

void MainWindow::onPlanetNameChanged(QString planetName)
{
	m_planetName = planetName;
	refreshTable(m_planetName, m_planetName, m_commodityName);
}

/*!
   \brief MainWindow::onCommodityNameChanged
   \param commodityName
   Apply filter after changing commodity name.
 */

void MainWindow::onCommodityNameChanged(QString commodityName)
{
	m_commodityName = commodityName;
	refreshTable(m_planetName, m_planetName, m_commodityName);
}
