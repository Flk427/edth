#ifndef CSELECTHELPER_H
#define CSELECTHELPER_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QCompleter>

namespace Ui {
class CSelectHelper;
}

class CSelectHelper : public QWidget
{
	Q_OBJECT

public:
	explicit CSelectHelper(QWidget *parent = 0);
	~CSelectHelper();

	void setTitle(const QString& text);
	QString getText();

private:
	Ui::CSelectHelper *ui;
	QString m_tableName;
	QSqlQueryModel* m_model;
	QSortFilterProxyModel* m_completearProxyModel;
	QSortFilterProxyModel* m_sourceProxyModel;
	QCompleter* m_mycompletear;

public slots:
	void setTable(QString tableName);
	void setFilter(QString value);

private slots:
	void onLabelTextChanged(QString text);
	void updateList(QString filter);
	void onListViewClicked(QModelIndex modelIndex);

signals:
	void textChanged(QString text);
};

#endif // CSELECTHELPER_H
