#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T00:25:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openFOAM-configurator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Buttons.cpp \
    Logger.cpp \
    Messanger.cpp \
    Tables.cpp \
    Console.cpp \
    Parser.cpp \
    Menu.cpp

HEADERS  += mainwindow.h \
    Buttons.h \
    Logger.h \
    Messanger.h \
    Tables.h \
    Console.h \
    Parser.h \
    Menu.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    test/removeLogs.sh
