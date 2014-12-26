#ifndef CADDSTATIONDIALOG_H
#define CADDSTATIONDIALOG_H

#include <QDialog>

#include "CAddSystemDialog.h"

namespace Ui {
class CAddStationDialog;
}

class CAddStationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CAddStationDialog(CAddSystemDialog* addSystemDialog, QWidget *parent = 0);
	void setup(QString stationName);
	~CAddStationDialog();

private:
	Ui::CAddStationDialog *ui;
	CAddSystemDialog* m_addSystemDialog;
	QString m_stationName;

private slots:
	void addSystemName(QString text);
};

#endif // CADDSTATIONDIALOG_H
