QT += testlib svg

CONFIG += qt console warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    ../../teekkarinSekoiluSeikkailut/Bus.cpp \
    ../../teekkarinSekoiluSeikkailut/BusLine.cpp \
    ../../teekkarinSekoiluSeikkailut/Stop.cpp \
    BusLineTest.cpp \
    main.cpp \
    suite.cpp

HEADERS += \
    ../../teekkarinSekoiluSeikkailut/Bus.h \
    ../../teekkarinSekoiluSeikkailut/BusLine.h \
    ../../teekkarinSekoiluSeikkailut/Stop.h \
    Suite.h \
    suite.hpp

INCLUDEPATH += \
    ../../teekkarinSekoiluSeikkailut

RESOURCES += \
    ../../teekkarinSekoiluSeikkailut/map.qrc
