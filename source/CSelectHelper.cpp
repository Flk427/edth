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

	m_model = new QSqlQueryModel(this);
	m_completearProxyModel = new QSortFilterProxyModel(this);
	m_sourceProxyModel = new QSortFilterProxyModel(this);
	m_mycompletear = new QCompleter(this);

	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onLabelTextChanged(QString)));
	connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListViewClicked(QModelIndex)));

	//	connect(ui->addToolButton, SIGNAL(clicked()), this, SLOT(test()));
}

CSelectHelper::~CSelectHelper()
{
	delete m_model;
	delete m_sourceProxyModel;
	delete m_completearProxyModel;
	delete m_mycompletear;

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

void CSelectHelper::setTable(QString tableName)
{
	m_tableName = tableName;
	updateList("");
}

void CSelectHelper::setFilter(QString value)
{
	ui->lineEdit->setText(value);
}

void CSelectHelper::onLabelTextChanged(QString text)
{
	updateList(text);
	emit textChanged(text);
}

void CSelectHelper::updateList(QString filter)
{
	if (!filter.isEmpty())
	{
		m_model->setQuery("SELECT id, name FROM " + m_tableName + " WHERE UPPER(name) LIKE '%" + filter + "%'");
	}
	else
	{
		m_model->setQuery("SELECT id, name FROM " + m_tableName);
	}

//	m_completearProxyModel->setSourceModel(m_model);
//	m_completearProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
//	m_completearProxyModel->setFilterKeyColumn(1);

	m_sourceProxyModel->setSourceModel(m_model);
	m_sourceProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	m_sourceProxyModel->setFilterKeyColumn(1);

	ui->listView->setModel(m_sourceProxyModel);
	ui->listView->setModelColumn(1);

//	m_mycompletear->setCaseSensitivity(Qt::CaseInsensitive);
//	m_mycompletear->setModel(m_completearProxyModel);
//	m_mycompletear->setCompletionColumn(1);
//	m_mycompletear->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
//	ui->comboBox->setCompleter(m_mycompletear);

	//	clearDropdownList();

	//	QString text = ui->comboBox->currentText();
	//	QString queryText = "SELECT name FROM " + m_tableName + " WHERE name LIKE '%" + text + "%' ORDER BY name";
	//	qDebug() << queryText;

	//	QSqlQuery query(queryText);
	//	if (query.exec())
	//	{
	//		while (query.next())
	//		{
	//			qDebug() << query.value("name").toString();
	//			ui->comboBox->addItem(query.value("name").toString());
	//		}
	//		ui->comboBox->setCurrentIndex(-1);
	//		ui->comboBox->setCurrentText(text);
	//		ui->comboBox->showPopup();
	//	}
	//	else
	//	{
	//		qDebug() << "query is not executed" << query.lastError().text();
	//	}
}

void CSelectHelper::onListViewClicked(QModelIndex modelIndex)
{
//	emit textChanged(modelIndex.data().toString());
	ui->lineEdit->setText(modelIndex.data().toString());
}
