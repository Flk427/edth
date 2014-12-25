#ifndef CSELECTHELPER_H
#define CSELECTHELPER_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QCompleter>
#include <QVector>

namespace Ui {
class CSelectHelper;
}

struct SItem
{
	int id;
	QString name;
};

class CSelectHelper : public QWidget
{
	Q_OBJECT

public:
	explicit CSelectHelper(QWidget *parent = 0);
	~CSelectHelper();

	void setTitle(const QString& text);
	QString getText();

	void setParentFilterName(const QString& value);
	void setParentFilterValue(const QString& value);

private:
	Ui::CSelectHelper *ui;
	QString m_tableName;
	QString nameFilter;
	QSqlQueryModel* m_model;
	QSortFilterProxyModel* m_sourceProxyModel;
	QString parentFilterName;
	QString parentFilterValue;

public slots:
	void setTable(QString tableName);
	void setFilter(QString value);

private slots:
	void updateList();
	void onListViewClicked(QModelIndex modelIndex);

signals:
	void textChanged(QString text);
	void listChanged(const QVector<SItem>& items);
};

#endif // CSELECTHELPER_H