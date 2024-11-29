TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        admin.c \
        fileoperations.c \
        finduserbyaccountnumber.c \
        main.c \
        mainmenu.c \
        transaction.c \
        user.c

HEADERS += \
    admin.h \
    bankaccount.h \
    fileoperations.h \
    finduserbyaccountnumber.h \
    mainmenu.h \
    transaction.h \
    user.h
