#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T10:29:50
#
#-------------------------------------------------

QT       += core gui
QT       += network

QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


RESOURCES     = icons.qrc

TARGET = hueApp
TEMPLATE = app

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    api.cpp \
    lightlistmodel.cpp \
    light.cpp \
    lightsform.cpp \
    formsinglelight.cpp \
    settings.cpp \
    setting.cpp \
    group.cpp \
    grouplistmodel.cpp \
    mygroupsform.cpp \
    mygrouplistmodel.cpp \
    huestate.cpp \
    costumelightlistmodel.cpp

HEADERS  += mainwindow.h \
    api.h \
    lightlistmodel.h \
    light.h \
    lightsform.h \
    formsinglelight.h \
    settings.h \
    setting.h \
    group.h \
    grouplistmodel.h \
    mygroupsform.h \
    mygrouplistmodel.h \
    huestate.h \
    costumelightlistmodel.h
FORMS    += mainwindow.ui \
    lightsform.ui \
    formsinglelight.ui \
    settings.ui \
    mygroupsform.ui

RESOURCES += \
    icons.qrc
