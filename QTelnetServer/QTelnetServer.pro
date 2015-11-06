########################################################################
#
# QTelnetServer
#   Qt 5.x
#
########################################################################


QT += core network
QT -= gui

TARGET = QTelnetServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
main.cpp \
    qtelnetserver.cpp \
    telnettcpserver.cpp \
    telnettcpclient.cpp \
    telnetlogic.cpp

HEADERS += \
    qtelnetserver.h \
    telnettcpserver.h \
    telnettcpclient.h \
    telnetlogic.h

