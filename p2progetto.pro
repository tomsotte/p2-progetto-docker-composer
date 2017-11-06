#-------------------------------------------------
#
# Project created by QtCreator 2017-08-02T15:46:10
#
#-------------------------------------------------

QT += core gui
QT += widgets

TARGET = DockerComposer
TEMPLATE = app

CONFIG += c++11
CONFIG += qt

# -Wno-expansion-to-defined only needed in linux
QMAKE_CXXFLAGS += -std=c++11 -Wno-expansion-to-defined

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

# Recursively find all files $$files(pattern, true)

SOURCES += \
	$$files(*.cpp, true)

HEADERS += \
	lib/json.hpp \
	$$files(*.h, true)

RESOURCES += \
    resources.qrc
