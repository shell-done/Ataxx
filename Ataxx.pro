#-------------------------------------------------
#
# Project created by QtCreator 2019-04-23T17:10:05
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ataxx
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_SCALE_FACTOR

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += console

SOURCES += \
    main.cpp \
    src/Core/board.cpp \
    src/Core/gamecore.cpp \
    src/Core/textures.cpp \
    src/Core/translator.cpp \
    src/Interface/Console/console.cpp \
    src/Interface/Graphic/Items/graphicsboarditem.cpp \
    src/Interface/Graphic/Items/graphicsbuttonitem.cpp \
    src/Interface/Graphic/Items/graphicsplayerframeitem.cpp \
    src/Interface/Graphic/Items/graphicstextcarouselitem.cpp \
    src/Interface/Graphic/Screens/boardscreen.cpp \
    src/Interface/Graphic/Screens/characterselectionscreen.cpp \
    src/Interface/Graphic/Screens/mainmenuscreen.cpp \
    src/Interface/Graphic/Screens/optionsscreen.cpp \
    src/Interface/Graphic/Screens/partyoptionsscreen.cpp \
    src/Interface/Graphic/Screens/texturespacksscreen.cpp \
    src/Interface/Graphic/window.cpp \
    src/utils.cpp \

HEADERS += \
    src/Core/board.h \
    src/Core/gamecore.h \
    src/Core/textures.h \
    src/Core/translator.h \
    src/Interface/Console/console.h \
    src/Interface/Graphic/Items/graphicsboarditem.h \
    src/Interface/Graphic/Items/graphicsbuttonitem.h \
    src/Interface/Graphic/Items/graphicsplayerframeitem.h \
    src/Interface/Graphic/Items/graphicstextcarouselitem.h \
    src/Interface/Graphic/Screens/boardscreen.h \
    src/Interface/Graphic/Screens/characterselectionscreen.h \
    src/Interface/Graphic/Screens/mainmenuscreen.h \
    src/Interface/Graphic/Screens/optionsscreen.h \
    src/Interface/Graphic/Screens/partyoptionsscreen.h \
    src/Interface/Graphic/Screens/screen.h \
    src/Interface/Graphic/Screens/texturespacksscreen.h \
    src/Interface/Graphic/window.h \ \
    src/utils.h

RESOURCES += \
    resources.qrc
