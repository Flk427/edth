#ifndef CADDSYSTEMDIALOG_H
#define CADDSYSTEMDIALOG_H

#include <QDialog>

namespace Ui {
class CAddSystemDialog;
}

class CAddSystemDialog : public QDialog
{
	Q_OBJECT

public:
	enum EAddMode {modeAdd, modeEdit};

	explicit CAddSystemDialog(QWidget *parent = 0);
	~CAddSystemDialog();

	void setup(QString name);
private:
	Ui::CAddSystemDialog *ui;

	EAddMode m_mode;
	int m_id;
	QString m_oldName;

private slots:
	void onAcceptClicked();
	void onTextChanged();
};

#endif // CADDSYSTEMDIALOG_H
