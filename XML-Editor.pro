QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CompressDecompress/compress.cpp \
    CompressDecompress/decompress.cpp \
    ErrorChecking/errorDetectionCorrection.cpp \
    Graph/graph.cpp \
    TreeStructure/Node.cpp \
    TreeStructure/xmlTree.cpp \
    codeeditor.cpp \
    formatting/xml_INDENTOR.cpp \
    graphvisulaization.cpp \
    linenumberarea.cpp \
    main.cpp \
    minifying/xml_minifier.cpp \
    networkwindow.cpp \
    utilities/utilities.cpp \
    visualize/visualize.cpp \
    xmlToJson/xmltojson.cpp \
    xml_editor.cpp \
    XML_parsing/XML_parsing.cpp \

HEADERS += \
    CompressDecompress/compress.h \
    CompressDecompress/decompress.h \
    ErrorChecking/errorDetectionCorrection.h \
    Graph/graph.h \
    codeeditor.h \
    TreeStructure/Node.h \
    TreeStructure/xmlTree.h \
    formatting/xml_INDENTOR.h \
    graphvisulaization.h \
    linenumberarea.h \
    minifying/xml_minifier.h \
    networkwindow.h \
    utilities/utilities.h \
    visualize/visualize.h \
    xmlToJson/xmltojson.h \
    xml_editor.h \
    XML_parsing/XML_parsing.h \

FORMS += \
    graphvisulaization.ui \
    networkwindow.ui \
    xml_editor.ui

TRANSLATIONS += \
    XML-Editor_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
