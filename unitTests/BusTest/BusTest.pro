QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.cpp \
    BusTest.cpp

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.h

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/assets/assets.qrc

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut
