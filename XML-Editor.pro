QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ErrorChecking/errorDetectionCorrection.cpp \
    TreeStructure/Node.cpp \
    TreeStructure/xmlTree.cpp \
    XMLcompression/compress.cpp \
    codeeditor.cpp \
    formatting/xml_INDENTOR.cpp \
    linenumberarea.cpp \
    main.cpp \
    minifying/xml_minifier.cpp \
    utilities/utilities.cpp \
    xmlToJson/xmltojson.cpp \
    xml_editor.cpp \
    XML_parsing/XML_parsing.cpp \

HEADERS += \
    ErrorChecking/errorDetectionCorrection.h \
    XMLcompression/compress.h \
    codeeditor.h \
    TreeStructure/Node.h \
    TreeStructure/xmlTree.h \
    formatting/xml_INDENTOR.h \
    linenumberarea.h \
    minifying/xml_minifier.h \
    utilities/utilities.h \
    xmlToJson/xmltojson.h \
    xml_editor.h \
    XML_parsing/XML_parsing.h \

FORMS += \
    xml_editor.ui

TRANSLATIONS += \
    XML-Editor_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
