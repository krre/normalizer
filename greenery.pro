QT += qml quick
CONFIG += c++11
TEMPLATE = app

win32 {
    release: DESTDIR = $$OUT_PWD
    debug:   DESTDIR = $$OUT_PWD
}

SOURCES += \
    src/cpp/main.cpp

DISTFILES += \
    README.md \
    src/qml/main.qml \
    src/qml/TopMenuBar.qml

RESOURCES += \
    src/greenery.qrc

