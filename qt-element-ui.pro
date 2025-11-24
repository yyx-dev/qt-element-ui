QT += core widgets gui svg

CONFIG += c++17 console

INC = components/
SRC = components/
EXM = examples
RES = resources
DEP = components/deprecated

GALLERY = examples/gallery


HEADERS += \
    $$files($$EXM/*.h) \
    $$files($$INC/*.h) \
    $$files($$DEP/*.h) \
    $$files($$GALLERY/*.h)

SOURCES += \
    $$files($$EXM/*.cpp) \
    $$files($$SRC/*.cpp) \
    $$files($$DEP/*.cpp) \
    $$files($$GALLERY/*.cpp)

FORMS += \
    $$files($$EXM/*.ui)

RESOURCES += \
    $$files($$RES/*.qrc)

INCLUDEPATH += \
    $$EXM \
    $$INC \
    $$DEP

TRANSLATIONS += \
    $$files($$RES/locales/*.ts)

win32 {
    LIBS += -lgdi32
}
