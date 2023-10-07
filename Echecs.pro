QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    echiquier.cpp \
    home.cpp \
    main.cpp \
    game.cpp \
    position.cpp \
    piece.cpp \
    roi.cpp \
    reine.cpp \
    fou.cpp \
    setting.cpp \
    tour.cpp \
    soldat.cpp \
    chevalier.cpp

HEADERS += \
    echiquier.h \
    game.h \
    home.h \
    setting.h \
    position.h \
    piece.h \
    roi.h \
    reine.h \
    fou.h \
    tour.h \
    soldat.h \
    chevalier.h

TRANSLATIONS += \
    Echecs_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS +=
