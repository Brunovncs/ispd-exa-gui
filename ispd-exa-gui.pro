SOURCES += \
  src/gridscene.cpp \
  src/gridview.cpp \
  src/main.cpp \
  src/mainwindow.cpp \
  src/userwindow.cpp \
  src/workloads.cpp \
  src/settingswindow.cpp \
  src/machineicon.cpp \
  src/clustericon.cpp \
  src/icon.cpp \
  src/link.cpp

INCLUDEPATH += include/
HEADERS += \
  include/mainwindow.h \
  include/userwindow.h \
  include/workloads.h \
  include/gridscene.h \
  include/gridview.h \
  include/settingswindow.h \
  include/machineicon.h \
  include/clustericon.h \
  include/icon.h \
  include/link.h

QT += widgets

CONFIG += c++17

RESOURCES += \
  ispd-exa-gui.qrc

FORMS += \
  forms/userwindow.ui \
  forms/workloads.ui \
  forms/mainwindow.ui \
  forms/settingswindow.ui

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

