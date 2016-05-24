QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

TARGET = CarePlanGenerator

SOURCES += *.cpp

HEADERS += *.h

FORMS   += *.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lCarePlanGenerator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lCarePlanGenerator
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lCarePlanGenerator

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

DISTFILES += carePlanIssues.json

install_it.path = $$OUT_PWD
install_it.files = $$PWD/*.json

INSTALLS += \
            install_it
