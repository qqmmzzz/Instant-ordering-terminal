# ============================================
# 点餐终端系统 - 服务器端 Qt 项目文件
# ============================================
QT       += core gui widgets network sql

TARGET   = OrderServer
TEMPLATE = app
CONFIG   += c++17

SOURCES += \
    main.cpp \
    serverwidget.cpp \
    mytcpserver.cpp \
    dbmanager.cpp \
    logindialog.cpp \
    adddishdialog.cpp \
    thememanager.cpp \
    themecolordialog.cpp \
    qrcodedialog.cpp

HEADERS += \
    serverwidget.h \
    mytcpserver.h \
    dbmanager.h \
    logindialog.h \
    adddishdialog.h \
    thememanager.h \
    themecolordialog.h \
    qrcodedialog.h

FORMS += \
    serverwidget.ui
