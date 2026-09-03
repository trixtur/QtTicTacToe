CONFIG += console
QT -= gui
QMAKE_LIBS_OPENGL =
TEMPLATE = app
TARGET = tictactoe_test
SOURCES += tictactoe_test.cpp \
           ../game.cpp \
           ../computerplayer.cpp
HEADERS += ../game.h
HEADERS += ../computerplayer.h
INCLUDEPATH += ..
