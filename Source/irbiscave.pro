QT += core gui widgets sql
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++11
TARGET = irbiscave
TEMPLATE = app

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

DEFINES += VERSION_MAJOR=$$VERSION_MAJOR \
    VERSION_MINOR=$$VERSION_MINOR \
    VERSION_PATCH=$$VERSION_PATCH \
    VERSION_STR=\"\\\"$$VERSION\\\"\"

SOURCES += \
    main.cpp \
    UI/MainWindow.cpp \
    UI/Cave.cpp \
    Db/DatabaseManager.cpp \
    UI/Options.cpp \
    Core/Settings.cpp

HEADERS += \
    UI/MainWindow.h \
    Core/Defines.h \
    UI/Cave.h \
    Db/DatabaseManager.h \
    UI/Options.h \
    Core/Singleton.h \
    Core/Settings.h

FORMS += \
    UI/MainWindow.ui \
    UI/Options.ui
