QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arista.cpp \
    button.cpp \
    circulovertice.cpp \
    dijkstra.cpp \
    dragwidget.cpp \
    grafo.cpp \
    infomostrar.cpp \
    informationPrim.cpp \
    main.cpp \
    vertice.cpp

HEADERS += \
    arista.h \
    arraylist.h \
    button.h \
    circulovertice.h \
    cola.h \
    dijkstra.h \
    dragwidget.h \
    grafo.h \
    infomostrar.h \
    informationPrim.h \
    list.h \
    nodo.h \
    pila.h \
    vertice.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/icono.ico
