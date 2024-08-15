QT += core gui widgets sql
QT += 3dcore 3drender 3dinput 3dextras

CONFIG += c++11
TARGET = irbiscave
TEMPLATE = app
DESTDIR = $$(IRBIS_HOME)/build

INCLUDEPATH += $$(IRBIS_HOME)/irbislib/Source

LIBS += -L$$(IRBIS_HOME)/build
LIBS += -lirbis

SOURCES += \
    main.cpp \
    UI/MainWindow.cpp \
    UI/Cave.cpp \
    Db/DatabaseManager.cpp \
    UI/Options.cpp \
    Core/Settings.cpp \
    UI/SelectWorkspace.cpp \
    UI/NewProject.cpp \
    UI/NewFile.cpp \
    UI/ProjectTreeView.cpp

HEADERS += \
    UI/MainWindow.h \
    Core/Defines.h \
    UI/Cave.h \
    Db/DatabaseManager.h \
    UI/Options.h \
    Core/Settings.h \
    UI/SelectWorkspace.h \
    UI/NewProject.h \
    UI/NewFile.h \
    UI/ProjectTreeView.h

FORMS += \
    UI/MainWindow.ui \
    UI/Options.ui \
    UI/SelectWorkspace.ui \
    UI/NewProject.ui \
    UI/NewFile.ui

DISTFILES += \
    ../README.md \
    ../.gitignore
