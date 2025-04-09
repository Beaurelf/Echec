QT       += core gui multimedia

win32 {
    LIBS += -LC:/FFmpeg/lib -lavcodec -lavformat -lavutil -lswscale
    INCLUDEPATH += C:/FFmpeg/include
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    case_echequier.cpp \
    echec_model.cpp \
    echiquier.cpp \
    home.cpp \
    main.cpp \
    game.cpp \
    pieceitem.cpp \
    position.cpp \
    piece.cpp \
    roi.cpp \
    reine.cpp \
    fou.cpp \
    tour.cpp \
    soldat.cpp \
    chevalier.cpp

HEADERS += \
    case_echequier.h \
    echec_model.h \
    echiquier.h \
    game.h \
    home.h \
    pieceitem.h \
    position.h \
    piece.h \
    roi.h \
    reine.h \
    fou.h \
    tour.h \
    soldat.h \
    chevalier.h \
    utils.h

TRANSLATIONS += \
    Echecs_fr_FR.ts
CONFIG += debug
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS +=


