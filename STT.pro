QT += sql

TARGET = myStudyTimeTable

symbian:TARGET.UID3 = 0xE639CADE
symbian:TARGET = myStudyTimeTable

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
