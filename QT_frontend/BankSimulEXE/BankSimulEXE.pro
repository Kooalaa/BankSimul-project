QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    main_window.cpp \
    nosta.cpp \
    saldo.cpp \
    selaa.cpp \
    start_window.cpp \
    talleta.cpp

HEADERS += \
    main_window.h \
    nosta.h \
    saldo.h \
    selaa.h \
    start_window.h \
    talleta.h

FORMS += \
    main_window.ui \
    nosta.ui \
    saldo.ui \
    selaa.ui \
    start_window.ui \
    talleta.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLPincode-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/ -lDLLPincode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLPincode-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLPincode

INCLUDEPATH += $$PWD/../DLLPincode
DEPENDPATH += $$PWD/../DLLPincode
