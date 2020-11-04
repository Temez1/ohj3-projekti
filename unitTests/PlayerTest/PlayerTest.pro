QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../teekkarinSekoiluSeikkailut/gameObjects/Wallet.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/BusLine.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Food.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Kiosk.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Player.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Teekkari.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/TeekkariHandler.cpp \
    PlayerTest.cpp

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/assets/assets.qrc

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/Wallet.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/BusLine.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Bus.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Food.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Kiosk.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Player.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Teekkari.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/BusLineHandler.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/handlers/TeekkariHandler.h

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut
