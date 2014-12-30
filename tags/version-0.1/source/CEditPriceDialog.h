#ifndef CEDITPRICEDIALOG_H
#define CEDITPRICEDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class CEditPriceDialog;
}

class CEditPriceDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CEditPriceDialog(QWidget *parent = 0);
	~CEditPriceDialog();

	int begin(int id);

private:
	Ui::CEditPriceDialog *ui;
	int m_id;
	int m_sell;
	int m_buy;

protected:
	bool eventFilter(QObject* obj, QEvent *event);

private slots:
	void onOk();
};

#endif // CEDITPRICEDIALOG_H
