#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T11:28:05
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEGARoster
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    crosterwindow.cpp \
    cpersonal.cpp \
    cdutytype.cpp \
    cduty.cpp \
    cdatabasemanager.cpp \
    cpersonaledit.cpp \
    cdutytypeedit.cpp \
    choliday.cpp \
    cprintform.cpp \
    cprealert.cpp

HEADERS  += cmainwindow.h \
    crosterwindow.h \
    cpersonal.h \
    cdutytype.h \
    cduty.h \
    cdatabasemanager.h \
    cpersonaledit.h \
    cdutytypeedit.h \
    choliday.h \
    cprintform.h \
    cprealert.h

FORMS    += cmainwindow.ui \
    crosterwindow.ui \
    cpersonaledit.ui \
    cdutytypeedit.ui \
    cprintform.ui \
    cprealert.ui

OTHER_FILES += \
    mr.sql \
    mr.bmp

RESOURCES += \
    megaroster.qrc
