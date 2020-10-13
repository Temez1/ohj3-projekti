QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../../teekkarinSekoiluSeikkailut/Bus.cpp \
    ../../../teekkarinSekoiluSeikkailut/BusLine.cpp \
    ../../../teekkarinSekoiluSeikkailut/Stop.cpp \
    BusTest.cpp

HEADERS += \
    ../../../teekkarinSekoiluSeikkailut/Bus.h \
    ../../../teekkarinSekoiluSeikkailut/BusLine.h \
    ../../../teekkarinSekoiluSeikkailut/Stop.h

INCLUDEPATH += \
    ../../../teekkarinSekoiluSeikkailut
