QT += core widgets gui svg

CONFIG += c++17


INC = components/include
SRC = components/src
EXM = examples
RES = resources


HEADERS += \
    $$files($$EXM/*.h) \
    $$files($$INC/*.h) \
    $$files($$INC/tools/*.h) \


SOURCES += \
    $$files($$EXM/*.cpp) \
    $$files($$SRC/*.cpp) \
    $$files($$SRC/tools/*.cpp) \


FORMS += \
    $$files($$EXM/*.ui)


RESOURCES += \
    $$files($$RES/*.qrc)


INCLUDEPATH += \
    $$EXM \
    $$INC


win32 {
    LIBS += -lgdi32
}


TRANSLATIONS += \
    $$files($$RES/locales/*.ts)
