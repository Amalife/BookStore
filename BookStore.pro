QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    instance.cpp \
    main.cpp \
    bookstore.cpp \
    order.cpp \
    ordtablemodel.cpp \
    report.cpp \
    reportwindow.cpp \
    reqtablemodel.cpp \
    request.cpp \
    storage.cpp \
    storetablemodel.cpp

HEADERS += \
    book.h \
    bookstore.h \
    instance.h \
    order.h \
    ordtablemodel.h \
    report.h \
    reportwindow.h \
    reqtablemodel.h \
    request.h \
    storage.h \
    storetablemodel.h

FORMS += \
    bookstore.ui \
    reportwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    books.txt \
    clients.txt
