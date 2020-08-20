QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += file_copies

#Application version information
VERSION = 1.0.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogs/aboutdialog.cpp \
    forms/main/mainwindow.cpp \
    forms/tablelistview/tablelistview.cpp \
    main.cpp

HEADERS += \
    connection.h \
    dialogs/aboutdialog.h \
    forms/main/mainwindow.h \
    forms/tablelistview/tablelistview.h

FORMS += \
    dialogs/aboutdialog.ui \
    forms/main/mainwindow.ui \
    forms/tablelistview/tablelistview.ui

TRANSLATIONS += \
    translations/minishop_uk_UA.ts

DISTFILES += \
    minishop.ini

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = images/minishop.ico
RESOURCES += \
    minishop.qrc

# copy database files to build dir
database.path    = DB
database.files   += DB/minishop.db

setting.path   = $${OUT_PWD}
setting.files   += minishop.ini

COPIES      += database
COPIES      += setting

