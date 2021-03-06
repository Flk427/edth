#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "CSelectHelper.h"
#include <QDebug>
#include <QEvent>
#include <QStringList>

#include "CAddSystemDialog.h"
#include "CAddStationDialog.h"
#include "CAddPriceDialog.h"
#include "CEditPriceDialog.h"
#include "internal.h"

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

	SSTATE state;

	QSqlDatabase m_db;
	QSqlQueryModel* m_model;
	QString m_dbFile;
	QStringList m_systemsFilter;

	QString m_systemName;
	QString m_planetName;
	QString m_commodityName;

	QStringList m_filterItems;
	CAddSystemDialog* m_addSystemDialog;
	CAddStationDialog* m_addStationDialog;
	CAddPriceDialog* m_addPriceDialog;
	CEditPriceDialog* m_editPriceDialog;

	void initialize();
	void refreshTable(const QString& system, const QString& planet, const QString& commodity);

	void closeEvent(QCloseEvent *event);
	void readSettings();
	void setupStationEditButton();

protected:
	bool eventFilter(QObject* obj, QEvent *event);

public slots:
	void clearFilter();
	void clearAllFilters();

private slots:
	void onSystemNameChanged(QString systemName);
	void onPlanetNameChanged(QString planetName);
	void onCommodityNameChanged(QString commodityName);

	void onSystemsListChanged(QVector<SItem> items);
	void onStationsListChanged(QVector<SItem> items);
	void onCommodityesListChanged(QVector<SItem> items);

	void addSystemName(QString text);
	void addStation(QString text);

	void onSetPriceClicked();

	void activatePriceButton();
	void priceEdit(QModelIndex index);

	void onSystemFilterTextChanged(const QString& newText);
	void onAddFilter();
};

#endif // MAINWINDOW_H
