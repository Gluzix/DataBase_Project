#-------------------------------------------------
#
# Project created by QtCreator 2020-01-27T22:49:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBaseProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        cinemahall.cpp \
        informdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        movie.cpp \
        registerwindow.cpp \
        seat.cpp

HEADERS += \
        cinemahall.h \
        informdialog.h \
        mainwindow.h \
        movie.h \
        registerwindow.h \
        seat.h

FORMS += \
        cinemahall.ui \
        informdialog.ui \
        mainwindow.ui \
        movie.ui \
        registerwindow.ui \
        seat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    databaseres.qrc

DISTFILES += \
    Resources/fonts/Roboto_Condensed/LICENSE.txt
