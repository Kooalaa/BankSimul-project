QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balance.cpp \
    browse_transactions.cpp \
    deposit.cpp \
    deposit_instructions.cpp \
    main.cpp \
    main_window.cpp \
    start_window.cpp \
    withdraw.cpp

HEADERS += \
    balance.h \
    browse_transactions.h \
    deposit.h \
    deposit_instructions.h \
    main_window.h \
    start_window.h \
    withdraw.h

FORMS += \
    balance.ui \
    browse_transactions.ui \
    deposit.ui \
    deposit_instructions.ui \
    main_window.ui \
    start_window.ui \
    withdraw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




win32: LIBS += -L$$PWD/../build-DLLPincode-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLPincode

INCLUDEPATH += $$PWD/../DLLPincode
DEPENDPATH += $$PWD/../DLLPincode

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLRestAPI-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/ -lDLLRestAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLRestAPI-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/ -lDLLRestAPI

INCLUDEPATH += $$PWD/../DLLRestAPI
DEPENDPATH += $$PWD/../DLLRestAPI
