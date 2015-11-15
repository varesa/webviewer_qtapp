# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    webviewer.cpp \
    main.cpp

QT += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

QMAKE_CXXFLAGS += -std=gnu++0x

HEADERS += \
    webviewer.h
