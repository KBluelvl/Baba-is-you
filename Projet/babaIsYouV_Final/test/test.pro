TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

win32-g++* {
    QMAKE_CXXFLAGS += -Wa,-mbig-obj
}

#QMAKE_CXXFLAGS += -DCATCH_CONFIG_DISABLE

include(../config.pri)

SOURCES += \
    Main.cpp \
    Tst_Board.cpp \
    Tst_Case.cpp \
    Tst_Loader.cpp

