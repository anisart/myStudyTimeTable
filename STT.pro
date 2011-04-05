QT += sql

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    row.cpp \
    editwindow.cpp

HEADERS += \
    mainwidget.h \
    row.h \
    database.h \
    editwindow.h

RESOURCES += \
    stt.qrc

OTHER_FILES += \
    style.qss \
    android/AndroidManifest.xml \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/res/drawable-ldpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-hdpi/icon.png
