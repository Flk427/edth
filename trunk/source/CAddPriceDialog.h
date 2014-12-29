#ifndef CADDPRICEDIALOG_H
#define CADDPRICEDIALOG_H

#include <QDialog>

namespace Ui {
class CAddPriceDialog;
}

class CAddPriceDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CAddPriceDialog(QWidget *parent = 0);
	~CAddPriceDialog();

	void setup(int station, int commodity);

private:
	Ui::CAddPriceDialog *ui;

	int m_station;
	int m_commodity;

	int m_sell;
	int m_buy;

private slots:
	void onAcceptClicked();
	void validateData();

};

#endif // CADDPRICEDIALOG_H
