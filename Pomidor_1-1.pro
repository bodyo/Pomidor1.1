#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T01:48:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pomidor_1-1
TEMPLATE = app

INCLUDEPATH += /usr/local/qwt-6.1.4-svn/include
LIBS += -L"/usr/local/qwt-6.1.4-svn/lib" -lqwt

SOURCES += main.cpp\
        mainwidget.cpp \
    stopwatch.cpp \
    timescalewidget.cpp

HEADERS  += mainwidget.h \
    stopwatch.h \
    timescalewidget.h

FORMS    += mainwidget.ui
