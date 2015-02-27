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
    cprealertedit.cpp \
    cprealert.cpp \
    cprealerttype.cpp \
    clogonassign.cpp \
    crule.cpp \
    cprinttable.cpp \
    cprinttablecell.cpp \
    cprinttablerow.cpp \
    cprinttablecol.cpp \
    cdtybasetype.cpp \
    croster.cpp \
    clogbookview.cpp \
    csingleprealertedit.cpp

HEADERS  += cmainwindow.h \
    crosterwindow.h \
    cpersonal.h \
    cdutytype.h \
    cduty.h \
    cdatabasemanager.h \
    cpersonaledit.h \
    cdutytypeedit.h \
    choliday.h \
    cprealertedit.h \
    cprealert.h \
    cprealerttype.h \
    clogonassign.h \
    crule.h \
    cprinttable.h \
    cprinttablecell.h \
    cprinttablerow.h \
    cprinttablecol.h \
    cdtybasetype.h \
    croster.h \
    clogbookview.h \
    csingleprealertedit.h

FORMS    += cmainwindow.ui \
    crosterwindow.ui \
    cpersonaledit.ui \
    cdutytypeedit.ui \
    cprealertedit.ui \
    clogonassign.ui \
    clogbookview.ui \
    csingleprealertedit.ui

OTHER_FILES += \
    mr.sql \
    mr.bmp \
    mr-data.sql

RESOURCES += \
    megaroster.qrc
