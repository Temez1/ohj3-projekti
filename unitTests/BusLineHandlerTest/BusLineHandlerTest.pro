QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.cpp \
    BusLineHandlerTest.cpp

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/assets/assets.qrc

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.h

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut/
