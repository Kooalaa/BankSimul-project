QT += gui network widgets svg

TEMPLATE = lib
DEFINES += DLLMOBILELOGIN_LIBRARY

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QR-Code-generator/cpp/QrCode.cpp \
    dll_mobile_login.cpp \
    network_handler.cpp \
    qr_display.cpp \
    qr_mobile_token.cpp

HEADERS += \
    DLLMobileLogin_global.h \
    QR-Code-generator/cpp/QrCode.hpp \
    dll_mobile_login.h \
    network_handler.h \
    qr_display.h \
    qr_mobile_token.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    qr_display.ui \
    qr_mobile_token.ui
