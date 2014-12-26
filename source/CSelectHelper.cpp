#include "CSelectHelper.h"
#include "ui_CSelectHelper.h"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

CSelectHelper::CSelectHelper(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CSelectHelper)
{
	ui->setupUi(this);
	hideClearButton();

	m_model = new QSqlQueryModel(this);
	m_sourceProxyModel = new QSortFilterProxyModel(this);

	// Сигнал для обновления таблицы результатов
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));
	// Подстановка результата в текстовое поле (вызовет сигнал для обновления таблицы результатов)
	connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListViewClicked(QModelIndex)));
	// Сигнал для обновления зависимых таблиц
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setFilter(QString)));
	// Сигнал нажатия на кнопку "очистить"
	connect(ui->clearToolButton, SIGNAL(clicked()), this, SLOT(clearFilter()));
	// Сигнал нажатия на кнопку "добавить"
	connect(ui->addToolButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
}

CSelectHelper::~CSelectHelper()
{
	delete m_model;
	delete m_sourceProxyModel;
	delete ui;
}

void CSelectHelper::setTitle(const QString& text)
{
	ui->label->setText(text);
}

QString CSelectHelper::getText()
{
	return ui->label->text();
}

void CSelectHelper::hideClearButton()
{
	ui->clearToolButton->hide();
}

void CSelectHelper::showClearButton()
{
	ui->clearToolButton->show();
}

void CSelectHelper::setParentFilterName(const QString& value)
{
	parentFilterName = value;
}

void CSelectHelper::setParentFilterValue(const QString& value)
{
	parentFilterValue = value;
	updateList();
}

void CSelectHelper::setTable(QString tableName)
{
	m_tableName = tableName;
	nameFilter = "";
	updateList();
}

void CSelectHelper::setFilter(QString value)
{
	ui->lineEdit->setText(value);
	nameFilter = value;
	updateList();
}

void CSelectHelper::clearFilter()
{
	setFilter("");
}

void CSelectHelper::updateList()
{
	QString query("SELECT id, name FROM " + m_tableName);

	if (!nameFilter.isEmpty() || !parentFilterValue.isEmpty())
	{
		query += " WHERE ";
	}

	if (!nameFilter.isEmpty())
	{
		query += "UPPER(name) LIKE '%" + nameFilter + "%'";

		if (!parentFilterValue.isEmpty())
		{
			query += " AND ";
		}
	}

	if (!parentFilterValue.isEmpty())
	{
		query += parentFilterName + " IN (" + parentFilterValue + ")";
	}

	query += " ORDER BY UPPER(name)";

	qDebug() << m_tableName << "query: " << query;

	m_model->setQuery(query);

	m_sourceProxyModel->setSourceModel(m_model);
	m_sourceProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_sourceProxyModel->setFilterKeyColumn(1);

	ui->listView->setModel(m_sourceProxyModel);
	ui->listView->setModelColumn(1);

	qDebug() << "READ:" << m_tableName;

	QVector<SItem> items;

	for (int i=0; i<ui->listView->model()->rowCount(); i++)
	{
		SItem item;
		item.id = ui->listView->model()->index(i, 0).data().toInt();
		item.name = ui->listView->model()->index(i, 1).data().toString();

		qDebug() << "id:" << item.id << "name:" << item.name;

		items.push_back(item);
	}

	emit listChanged(items);
}

void CSelectHelper::onListViewClicked(QModelIndex modelIndex)
{
	ui->lineEdit->setText(modelIndex.data().toString());
}

void CSelectHelper::onAddButtonClicked()
{
	emit addButtonClicked(ui->lineEdit->text());
}
