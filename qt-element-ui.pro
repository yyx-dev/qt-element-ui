QT += core widgets gui svg

CONFIG += c++17 console

SRC = components/
PRI = components/private
EXM = example
RES = resources
GAL = gallery


HEADERS += \
    $$files($$EXM/*.h) \
    $$files($$SRC/*.h) \
    $$files($$PRI/*.h) \
    $$files($$GAL/*.h)

SOURCES += \
    $$files($$EXM/*.cpp) \
    $$files($$SRC/*.cpp) \
    $$files($$PRI/*.cpp) \
    $$files($$GAL/*.cpp)

FORMS += \
    $$files($$EXM/*.ui)

RESOURCES += \
    $$files($$RES/*.qrc) \
    $$files($$GAL/*.qrc)

INCLUDEPATH += \
    $$EXM \
    $$SRC \
    $$PRI \
    $$GAL

TRANSLATIONS += \
    $$files($$RES/locales/*.ts)

win32 {
    LIBS += -lgdi32 -ldwmapi
}
