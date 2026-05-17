# ============================================
# 点餐终端系统 - 客户端 Qt 项目文件
# ============================================
QT       += core gui widgets network

TARGET   = OrderClient
TEMPLATE = app
CONFIG   += c++17

SOURCES += \
    main.cpp \
    clientwidget.cpp \
    mytcpclient.cpp \
    dishitemwidget.cpp \
    cartitemwidget.cpp \
    cartmanager.cpp \
    thememanager.cpp \
    themecolordialog.cpp \
    qrcodedialog.cpp \
    numpadwidget.cpp \
    alphakeyboardwidget.cpp

HEADERS += \
    clientwidget.h \
    mytcpclient.h \
    dishitemwidget.h \
    cartitemwidget.h \
    cartmanager.h \
    thememanager.h \
    themecolordialog.h \
    qrcodedialog.h \
    numpadwidget.h \
    alphakeyboardwidget.h

FORMS += \
    clientwidget.ui
