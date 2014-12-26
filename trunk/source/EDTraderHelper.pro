#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T13:43:38
#
#-------------------------------------------------

QT       += core gui sql

win32-g++ {
	QMAKE_CXXFLAGS += -std=gnu++0x
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EDTraderHelper
TEMPLATE = app


SOURCES += main.cpp\
		MainWindow.cpp \
	CSelectHelper.cpp \
    CAddSystemDialog.cpp

HEADERS  += MainWindow.h \
	CSelectHelper.h \
    CAddSystemDialog.h

FORMS    += MainWindow.ui \
	CSelectHelper.ui \
    CAddSystemDialog.ui

DISTFILES += \
	dbtools/createQuery.cmd \
	dbtools/goods.list
