TEMPLATE = app
TARGET = STT

CONFIG += mobility
MOBILITY = multimedia \
    systeminfo

QT += sql

symbian: {
    TARGET = STT
    TARGET.UID3 = 0xE639CADE

    TARGET.CAPABILITY += ReadUserData \
        WriteUserData \
        LocalServices \
        UserEnvironment
}

SOURCES += \
    main.cpp \
    row.cpp \
    timetable.cpp \
    mainwindow.cpp \
    editwindow.cpp \
    camera.cpp \
    button.cpp

HEADERS += \
    database.h \
    row.h \
    timetable.h \
    mainwindow.h \
    editwindow.h \
    camera.h \
    button.h

RESOURCES += \
    resources.qrc
