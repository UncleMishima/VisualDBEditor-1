QT += gui widgets testlib

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testxmldb.cpp \
    ../../src/VisualDBEditor/AbstractDB.cpp \
    ../../src/VisualDBEditor/Table.cpp \
    ../../src/VisualDBEditor/XmlDB.cpp

HEADERS += \
    ../../src/VisualDBEditor/AbstractDB.h \
    ../../src/VisualDBEditor/Table.h \
    ../../src/VisualDBEditor/XmlDB.h

INCLUDEPATH += ../../src/VisualDBEditor/

include( ../../common.pri )
