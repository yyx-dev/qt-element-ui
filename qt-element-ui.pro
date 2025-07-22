QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


HEADERS += \
    components/include/container.h \
    components/include/color.h \
    components/include/button.h \
    components/include/text.h \
    components/include/scrollbar.h \
    tools/include/fontmanager.h \
    tools/include/commvar.h \
    tools/include/qsshelper.h \
    tools/include/iconmanager.h \
    example/include/mainwindow.h \
    tools/include/logger.h


SOURCES += \
    components/src/container.cpp \
    components/src/scrollbar.cpp \
    components/src/button.cpp \
    components/src/text.cpp \
    tools/src/logger.cpp \
    tools/src/fontmanager.cpp \
    tools/src/commvar.cpp \
    tools/src/qsshelper.cpp \
    tools/src/iconmanager.cpp \
    example/src/main.cpp \
    example/src/mainwindow.cpp \


FORMS += \
    example/mainwindow.ui


RESOURCES += \
    fonts.qrc \
    icons.qrc

