######################################################################
# Automatically generated by qmake (3.1) Mon May 30 10:26:08 2022
######################################################################
QT       += core network

TEMPLATE = app
TARGET = ssr.chug
QMAKE_CLEAN += $(TARGET)
QMAKE_DISTCLEAN += $(TARGET)
QMAKE_DISTCLEAN +=  .qmake.stash
QMAKE_DISTCLEAN +=  Makefile
INCLUDEPATH += .
INCLUDEPATH += chuck/include/
DEFINES += "__LINUX_ALSA__"
DEFINES += "__PLATFORM_LINUX__"
QMAKE_LFLAGS += "-shared -lstdc++"

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += ssr.cpp \
    tcp.cpp

HEADERS += \
    tcp.h
