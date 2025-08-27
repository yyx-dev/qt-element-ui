QT += core widgets gui svg

CONFIG += c++11

TOOLS_INC = components/include/tools
BASIC_INC = components/include/basic
FORM_INC  = components/include/form
DATA_INC  = components/include/data
NAVI_INC  = components/include/navigation
FDBK_INC  = components/include/feedback
OTHR_INC  = components/include/others

TOOLS_SRC = components/src/tools
BASIC_SRC = components/src/basic
FORM_SRC  = components/src/form
DATA_SRC  = components/src/data
NAVI_SRC  = components/src/navigation
FDBK_SRC  = components/src/feedback
OTHR_SRC  = components/src/others

EXMP_INC  = example/include
EXMP_SRC  = example/src


HEADERS += \
    $$EXMP_INC/mainwindow.h \
    $$TOOLS_INC/fontmanager.h $$TOOLS_INC/commvar.h $$TOOLS_INC/qsshelper.h $$TOOLS_INC/iconmanager.h  $$TOOLS_INC/logger.h $$TOOLS_INC/dpiscaler.h \
    $$BASIC_INC/container.h $$BASIC_INC/color.h $$BASIC_INC/button.h $$BASIC_INC/text.h $$BASIC_INC/scrollbar.h $$BASIC_INC/link.h \
    $$FORM_INC/input.h \


SOURCES += \
    $$EXMP_SRC/main.cpp $$EXMP_SRC/mainwindow.cpp \
    $$TOOLS_SRC/fontmanager.cpp $$TOOLS_SRC/commvar.cpp $$TOOLS_SRC/qsshelper.cpp $$TOOLS_SRC/iconmanager.cpp $$TOOLS_SRC/logger.cpp $$TOOLS_SRC/dpiscaler.cpp\
    $$BASIC_SRC/link.cpp $$BASIC_SRC/container.cpp $$BASIC_SRC/scrollbar.cpp $$BASIC_SRC/button.cpp $$BASIC_SRC/text.cpp \
    $$FORM_SRC/input.cpp \


FORMS += \
    example/mainwindow.ui


RESOURCES += \
    resources/fonts.qrc resources/icons.qrc


INCLUDEPATH += \
    $$EXMP_INC $$TOOLS_INC \
    $$BASIC_INC $$FORM_INC $$DATA_INC $$NAVI_INC $$FDBK_INC $$OTHR_INC


win32 {
    LIBS += -lgdi32
}


TRANSLATIONS = app_en_US.ts \
               app_zh_CN.ts
