#-------------------------------------------------
#
# Project created by QtCreator 2012-08-19T19:27:49
#
#-------------------------------------------------

QT       += core gui

TARGET = integration
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tritbot.cpp \
    triton.cpp \
    channel.cpp

HEADERS  += mainwindow.h \
    tritbot.h \
    triton.h \
    channel.h

FORMS    += mainwindow.ui
QT+=network
