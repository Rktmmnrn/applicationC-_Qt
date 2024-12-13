QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += -Wno-deprecated-copy

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avertissement.cpp \
    avertissement2.cpp \
    detailsmateriels.cpp \
    entretientmateriels.cpp \
    facture.cpp \
    listmateriels.cpp \
    main.cpp \
    mainwindow.cpp \
    materiel.cpp \
    modifentretientmateriels.cpp \
    modifmat.cpp \
    stylesheet.cpp

HEADERS += \
    avertissement.h \
    avertissement2.h \
    connectbdd.h \
    detailsmateriels.h \
    entretientmateriels.h \
    facture.h \
    listmateriels.h \
    mainwindow.h \
    materiel.h \
    modifentretientmateriels.h \
    modifmat.h \
    stylesheet.h

FORMS += \
    avertissement.ui \
    avertissement2.ui \
    detailsmateriels.ui \
    entretientmateriels.ui \
    facture.ui \
    listmateriels.ui \
    mainwindow.ui \
    materiel.ui \
    modifentretientmateriels.ui \
    modifmat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
