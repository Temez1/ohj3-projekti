QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../../teekkarinSekoiluSeikkailut/Bus.cpp \
    ../../../teekkarinSekoiluSeikkailut/BusLine.cpp \
    ../../../teekkarinSekoiluSeikkailut/Player.cpp \
    ../../../teekkarinSekoiluSeikkailut/Stop.cpp \
    PlayerTest.cpp

RESOURCES += \
    ../../../teekkarinSekoiluSeikkailut/map.qrc

HEADERS += \
    ../../../teekkarinSekoiluSeikkailut/Bus.h \
    ../../../teekkarinSekoiluSeikkailut/BusLine.h \
    ../../../teekkarinSekoiluSeikkailut/Player.h \
    ../../../teekkarinSekoiluSeikkailut/Stop.h

INCLUDEPATH += \
    ../../../teekkarinSekoiluSeikkailut
