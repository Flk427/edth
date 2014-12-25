#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "CSelectHelper.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	QSqlDatabase m_db;
	QSqlQueryModel* m_model;
	QString m_dbFile;

	QString m_systemName;
	QString m_planetName;
	QString m_commodityName;

	void initialize();
	void refreshTable(const QString& system, const QString& planet, const QString& commodity);

	void closeEvent(QCloseEvent *event);
	void readSettings();

public slots:
	void clearFilter();

private slots:
	void onSystemNameChanged(QString systemName);
	void onPlanetNameChanged(QString planetName);
	void onCommodityNameChanged(QString commodityName);

	void onSystemsListChanged(QVector<SItem> items);
};

#endif // MAINWINDOW_H
