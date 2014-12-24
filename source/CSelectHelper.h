#ifndef CSELECTHELPER_H
#define CSELECTHELPER_H

#include <QWidget>

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

private slots:
	void onLabelTextChanged(QString text);

signals:
	void textChanged(QString text);
};

#endif // CSELECTHELPER_H
