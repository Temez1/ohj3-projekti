QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../teekkarinSekoiluSeikkailut/gameObjects/BusLine.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Food.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Teekkari.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/TeekkariHandler.cpp \
    TeekkariHandlerTest.cpp

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/assets/assets.qrc

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/BusLine.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Food.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Teekkari.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/TeekkariHandler.h

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut
