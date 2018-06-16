#-------------------------------------------------
#
# Project created by QtCreator 2018-06-16T13:52:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SOP-Converter
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    logging/Logger/Logger.cpp \
    logging/Messanger/Messanger.cpp \
    Ui/Buttons/Buttons.cpp \
    Ui/Console/Console.cpp \
    Ui/Menu/Menu.cpp \
    Ui/Tables/Tables.cpp \
    configuration/Parser/Parser.cpp \
    Ui/Buttons/ButtonsGroup.cpp \
    Ui/Console/ConsoleAndButtonsGroup.cpp \
    Ui/Tables/TableAndEtcGroup.cpp

HEADERS  += MainWindow.h \
    logging/Logger/Logger.h \
    logging/Messanger/Messanger.h \
    Ui/Buttons/Buttons.h \
    Ui/Console/Console.h \
    Ui/Menu/Menu.h \
    Ui/Tables/Tables.h \
    configuration/Parser/Parser.h \
    Ui/Buttons/ButtonsGroup.h \
    Ui/Console/ConsoleAndButtonsGroup.h \
    Ui/Tables/TableAndEtcGroup.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    test/valgrind_test.sh \
    test/removeLogs.sh
