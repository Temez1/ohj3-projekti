QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/BusLine.cpp \
    BusLineTest.cpp

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/assets/assets.qrc

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/BusLine.h

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut/
