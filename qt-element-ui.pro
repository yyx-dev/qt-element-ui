QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


HEADERS += \
    components/include/container.h \
    components/include/color.h \
    components/include/button.h \
    components/include/text.h \
    components/include/scrollbar.h \
    components/include/link.h \
    tools/include/fontmanager.h \
    tools/include/commvar.h \
    tools/include/qsshelper.h \
    tools/include/iconmanager.h \
    tools/include/logger.h \
    example/include/mainwindow.h


SOURCES += \
    components//src/link.cpp \
    components/src/container.cpp \
    components/src/scrollbar.cpp \
    components/src/button.cpp \
    components/src/text.cpp \
    tools/src/fontmanager.cpp \
    tools/src/commvar.cpp \
    tools/src/qsshelper.cpp \
    tools/src/iconmanager.cpp \
    tools/src/logger.cpp \
    example/src/main.cpp \
    example/src/mainwindow.cpp


FORMS += \
    example/mainwindow.ui


RESOURCES += \
    fonts.qrc \
    icons.qrc

