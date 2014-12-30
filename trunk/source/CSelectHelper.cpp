#include "CSelectHelper.h"
#include "ui_CSelectHelper.h"

#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringListModel>
#include <QKeyEvent>

CSelectHelper::CSelectHelper(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CSelectHelper)
{
	ui->setupUi(this);

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

	ui->listView->installEventFilter(this);
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
	return ui->lineEdit->text();
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
	qDebug() << "CSelectHelper::setParentFilterValue:" << value;
	parentFilterValue = value;
	updateList();
}

int CSelectHelper::getItemsCount()
{
	return ui->listView->model()->rowCount();
}

void CSelectHelper::setTable(QString tableName)
{
	m_tableName = tableName;
	nameFilter = "";
	updateList();
}

void CSelectHelper::setFilter(QString value)
{
	qDebug() << "CSelectHelper::setFilter:" << value;
	ui->lineEdit->setText(value);
	nameFilter = value;
	updateList();
}

void CSelectHelper::clearFilter()
{
	setFilter("");
}

void CSelectHelper::setEditButtonEnabled(bool enabled)
{
	ui->addToolButton->setEnabled(enabled);
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

	connect(ui->listView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(onSelectionChanged(QModelIndex,QModelIndex)));

	ui->listView->setModelColumn(1);

	qDebug() << "READ:" << m_tableName;

	QVector<SItem> items;

//	if (!ui->lineEdit->text().isEmpty())
	{
		for (int i=0; i<ui->listView->model()->rowCount(); i++)
		{
			SItem item;
			item.id = ui->listView->model()->index(i, 0).data().toInt();
			item.name = ui->listView->model()->index(i, 1).data().toString();

			//		qDebug() << "id:" << item.id << "name:" << item.name;

			items.push_back(item);
		}
	}

	emit listChanged(items);
}

void CSelectHelper::onListViewClicked(QModelIndex modelIndex)
{
	ui->lineEdit->setText(modelIndex.data().toString());
//	int id = ui->listView->model()->index(ui->listView->currentIndex().row(), 0).data().toInt();
//	qDebug() << "CSelectHelper::onListViewClicked id =" << id;
}

void CSelectHelper::onAddButtonClicked()
{
	emit addButtonClicked(ui->lineEdit->text());
}

void CSelectHelper::onSelectionChanged(const QModelIndex& i1, const QModelIndex& i2)
{
	qDebug() << "CSelectHelper::onSelectionChanged"
			 << ui->listView->model()->index(i1.row(), 0).data().toInt()
			 << ui->listView->model()->index(i1.row(), 1).data().toString();
//	emit textChanged(i1.data().toString());

	QVector<SItem> items;
	SItem item;
	item.id = ui->listView->model()->index(i1.row(), 0).data().toInt();
	item.name = ui->listView->model()->index(i1.row(), 1).data().toString();
	items.push_back(item);
	emit listChanged(items);

//	qDebug() << ui->listView->selectionModel()->selectedRows()[0].data().toString();
//	qDebug() << selection.indexes().first().data().toString();
//	if (!selection.indexes().isEmpty())
//	{
//		qDebug() << selection.indexes().first().data().toString();
//	}
}

bool CSelectHelper::eventFilter(QObject* obj, QEvent *event)
{
	if (obj == ui->listView)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if(keyEvent->key() == Qt::Key_Return)
			{
				qDebug() << "listView -> Qt::Key_Return";
				emit enterPressed();
				return true;
			}
		}
		return false;
	}
	return QWidget::eventFilter(obj, event);
}
