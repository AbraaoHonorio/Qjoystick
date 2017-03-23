#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T15:56:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qjoystick
TEMPLATE = app

UBUNTU_RELEASE = $$system(lsb_release -cs)

equals(UBUNTU_RELEASE, trusty): ROS_VERSION = "indigo"
else: equals(UBUNTU_RELEASE, xenial): ROS_VERSION = "kinetic"
else: error(Esse sistema operacional não é suportado.)

ROS_PATH = /opt/ros/$$ROS_VERSION

DEPENDPATH += $$ROS_PATH/include
INCLUDEPATH += $$ROS_PATH/include
LIBS += -L$$ROS_PATH/lib

# Adicione todas as bibliotecas necessárias logo abaixo
LIBS += \
    -lroscpp \
    -lrosconsole \
    -lroscpp_serialization \
    -lrostime \
    -lxmlrpcpp \
    -lcpp_common \
    -lrosconsole_log4cxx \
    -lrosconsole_backend_interface

# <-- Teste para localização do ROS --> #

SOURCES += main.cpp\
        joystickwindow.cpp \
    joystick.cpp \
    qjoystick.cpp

HEADERS  += joystickwindow.h \
    joystick.h \
    qjoystick.h

FORMS    += joystickwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
