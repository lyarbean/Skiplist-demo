TEMPLATE = app

QT += qml quick 

SOURCES += main.cpp \
    skiplist.cpp \
    skiplistmodel.cpp
    

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

CONFIG += c++11  qt plugin

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    skiplist.h \
    skiplistmodel.h 

