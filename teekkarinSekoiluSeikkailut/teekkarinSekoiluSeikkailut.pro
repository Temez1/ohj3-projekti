QT += core gui svg widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameObjects.cpp \
    MainMenu.cpp \
    UI/Lautanen.cpp \
    UI/ProgressBar.cpp \
    UI/handlers/Lautaset.cpp \
    gameObjects.cpp \
    gameObjects/BusLine.cpp \
    gameObjects/Wallet.cpp \
    gameObjects/handlers/BusLineHandler.cpp \
    initScene.cpp \
    main.cpp \
    Game.cpp \
    gameObjects/graphical/Bus.cpp \
    gameObjects/graphical/Food.cpp \
    gameObjects/graphical/Kiosk.cpp \
    gameObjects/graphical/Player.cpp \
    gameObjects/graphical/Stop.cpp \
    gameObjects/graphical/Teekkari.cpp \
    gameObjects/handlers/TeekkariHandler.cpp

HEADERS += \
    Game.h \
    GameObjects.h \
    MainMenu.h \
    UI/Lautanen.h \
    UI/ProgressBar.h \
    UI/handlers/Lautaset.h \
    gameObjects.h \
    gameObjects/BusLine.h \
    gameObjects/Wallet.h \
    gameObjects/graphical/Bus.h \
    gameObjects/graphical/Food.h \
    gameObjects/graphical/Kiosk.h \
    gameObjects/graphical/Player.h \
    gameObjects/graphical/Stop.h \
    gameObjects/graphical/Teekkari.h \
    gameObjects/handlers/BusLineHandler.h \
    gameObjects/handlers/TeekkariHandler.h \
    initScene.h

RESOURCES += \
    gameObjects/graphical/assets/assets.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    MainMenu.ui
