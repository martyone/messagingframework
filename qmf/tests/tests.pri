QT -= gui
QT += testlib
CONFIG += unittest

macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET=10.5
}

equals(QT_MAJOR_VERSION, 4){
    LIBS += -lqmfclient
    target.path += /opt/tests/qmf
}
equals(QT_MAJOR_VERSION, 5){
    LIBS += -lqmfclient5
    target.path += /opt/tests/qmf-qt5
}

QMFPATH=../../src/libraries/qmfclient
DEPENDPATH += .
INCLUDEPATH += . $$QMFPATH $$QMFPATH/support
LIBS += -L$$QMFPATH/build

macx:LIBS += -F$$QMFPATH/build
QMAKE_LFLAGS += -Wl,-rpath,$$QMFPATH

include(../common.pri)

