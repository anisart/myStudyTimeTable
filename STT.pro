QT += sql

TEMPLATE = app
TARGET = myStudyTimeTable
VERSION = 1.0
ICON = icon.svg

symbian: {
    TARGET.UID3 = 0xE639CADE
    TARGET = myStudyTimeTable
    TARGET.CAPABILITY +=
}

SOURCES += \
    main.cpp \
    row.cpp \
    timetable.cpp \
    mainwindow.cpp \
    editwindow.cpp \
    viewwindowlist.cpp

HEADERS += \
    database.h \
    row.h \
    timetable.h \
    mainwindow.h \
    editwindow.h \
    viewwindowlist.h
