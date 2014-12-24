#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T13:43:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EDTraderHelper
TEMPLATE = app


SOURCES += main.cpp\
		MainWindow.cpp \
	CSelectHelper.cpp

HEADERS  += MainWindow.h \
	CSelectHelper.h

FORMS    += MainWindow.ui \
	CSelectHelper.ui

DISTFILES += \
    dbtools/createQuery.cmd \
    dbtools/goods.list
