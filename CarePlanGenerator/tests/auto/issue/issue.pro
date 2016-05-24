QT     += testlib
QT     -= gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES += *.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../src/lib/release/ -lCarePlanGenerator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/lib/debug/ -lCarePlanGenerator
else:unix: LIBS += -L$$OUT_PWD/../../../src/lib/ -lCarePlanGenerator

INCLUDEPATH += $$PWD/../../../src/lib
DEPENDPATH += $$PWD/../../../src/lib
