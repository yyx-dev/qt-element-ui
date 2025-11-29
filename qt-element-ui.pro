QT += core widgets gui svg

CONFIG += c++17 console

SRC = components/
DEP = components/deprecated
EXM = examples
RES = resources
GAL = gallery


HEADERS += \
    $$files($$EXM/*.h) \
    $$files($$SRC/*.h) \
    $$files($$DEP/*.h) \
    $$files($$GAL/*.h)

SOURCES += \
    $$files($$EXM/*.cpp) \
    $$files($$SRC/*.cpp) \
    $$files($$DEP/*.cpp) \
    $$files($$GAL/*.cpp)

FORMS += \
    $$files($$EXM/*.ui)

RESOURCES += \
    $$files($$RES/*.qrc) \
    $$files($$GAL/*.qrc)

INCLUDEPATH += \
    $$EXM \
    $$SRC \
    $$DEP \
    $$GAL

TRANSLATIONS += \
    $$files($$RES/locales/*.ts)

win32 {
    LIBS += -lgdi32
}
