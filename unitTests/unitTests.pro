QT += testlib widgets svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../teekkarinSekoiluSeikkailut/Bus.cpp \
    ../teekkarinSekoiluSeikkailut/BusLine.cpp \
    tst_busline.cpp

HEADERS += \
    ../teekkarinSekoiluSeikkailut/Bus.h \
    ../teekkarinSekoiluSeikkailut/BusLine.h

INCLUDEPATH += \
    ../teekkarinSekoiluSeikkailut
