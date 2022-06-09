QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ioifmanager.cpp \
    linuxserialoutput.cpp \
    main.cpp \
    qteditlinuxserialoutput.cpp \
    qtmainwindow.cpp \
    qtnewoutputdialog.cpp \
    qtoifuiedithandler.cpp

HEADERS += \
    baseoutputinterface.h \
    basetypes.h \
    ioifmanager.h \
    linuxserialoutput.h \
    qteditlinuxserialoutput.h \
    qtmainwindow.h \
    qtnewoutputdialog.h \
    qtoifuiedithandler.h

FORMS += \
    qteditlinuxserialoutput.ui \
    qtmainwindow.ui \
    qtnewoutputdialog.ui

CONFIG += c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
