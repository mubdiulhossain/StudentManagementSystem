#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T23:00:23
#
#-------------------------------------------------

QT       += core gui widgets
QT       += sql

TARGET = StudentManagementSystemQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        logIndialog.cpp \
    Academician.cpp \
    Admin.cpp \
    Course.cpp \
    Diploma.cpp \
    DiplomaCourse.cpp \
    Faculty.cpp \
    PostGraduate.cpp \
    PostGraduateCourse.cpp \
    Student.cpp \
    Trimester.cpp \
    Trimester1.cpp \
    Trimester2.cpp \
    Trimester3.cpp \
    UnderGraduate.cpp \
    UnderGraduateCourse.cpp \
    User.cpp \
    mainmenu.cpp \
    delegatecombobox.cpp \
    noteditabledelegate.cpp \
    postgresdatabase.cpp

HEADERS += \
        logIndialog.h \
    Academician.h \
    Admin.h \
    Course.h \
    Diploma.h \
    DiplomaCourse.h \
    Faculty.h \
    PostGraduate.h \
    PostGraduateCourse.h \
    Student.h \
    Trimester.h \
    Trimester1.h \
    Trimester2.h \
    Trimester3.h \
    UnderGraduate.h \
    UnderGraduateCourse.h \
    User.h \
    mainmenu.h \
    delegatecombobox.h \
    noteditabledelegate.h \
    postgresdatabase.h


FORMS += \
        logIndialog.ui \
    mainmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    StudentManagementSystemQT.pro

DISTFILES +=

RESOURCES += \
    logo.qrc
