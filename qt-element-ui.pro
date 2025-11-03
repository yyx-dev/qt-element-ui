QT += core widgets gui svg

CONFIG += c++17 console

INC = components/include
SRC = components/src
EXM = examples
RES = resources


HEADERS += \
    $$files($$EXM/*.h) \
    $$files($$INC/*.h)

SOURCES += \
    $$files($$EXM/*.cpp) \
    $$files($$SRC/*.cpp)

FORMS += \
    $$files($$EXM/*.ui)

RESOURCES += \
    $$files($$RES/*.qrc)

INCLUDEPATH += \
    $$EXM \
    $$INC

TRANSLATIONS += \
    $$files($$RES/locales/*.ts)

win32 {
    LIBS += -lgdi32
}
