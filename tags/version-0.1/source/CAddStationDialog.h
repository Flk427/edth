#ifndef CADDSTATIONDIALOG_H
#define CADDSTATIONDIALOG_H

#include <QDialog>

#include "CAddSystemDialog.h"
#include "internal.h"

namespace Ui {
class CAddStationDialog;
}

class CAddStationDialog : public QDialog
{
	Q_OBJECT

public:
	enum EAddMode {modeAdd, modeEdit};

	explicit CAddStationDialog(QWidget *parent = 0);
	void setup(PSSTATE pState, QString newName);
	~CAddStationDialog();

private:
	Ui::CAddStationDialog *ui;

	EAddMode m_mode;
	int m_id;
	QString m_oldName;
	QString m_newName;
	PSSTATE m_pState;

private slots:
	void onAcceptClicked();
	void onTextChanged();
};

#endif // CADDSTATIONDIALOG_H
