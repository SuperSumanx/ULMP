TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -Wno-sign-compare -Wno-write-strings


SOURCES += main.cpp \
    ulmp.cpp

HEADERS += \
    Array.h \
    ulmp.h

