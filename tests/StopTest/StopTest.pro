QT += testlib svg
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Food.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Kiosk.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.cpp \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Teekkari.cpp \
    StopTest.cpp

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Food.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Kiosk.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Stop.h \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/Teekkari.h

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/gameObjects/graphical/assets/assets.qrc
