#ifndef XML_EDITOR_H
#define XML_EDITOR_H



#include <QMainWindow>
#include "ui_xml_editor.h"
#include "customWidgets/codeeditor.h"
#include <QFile>
#include <Qdir>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include "ErrorChecking/errorDetectionCorrection.h"
#include <string>
#include "formatting/xml_INDENTOR.h"
#include "minifying/xml_minifier.h"
#include <sstream>
#include "xmlToJson/xmltojson.h"
#include "CompressDecompress/compress.h"
#include <stack>
#include <QTextCharFormat>
#include "CompressDecompress/decompress.h"
#include "Graph/graph.h"
#include "visualize/visualize.h"

QT_BEGIN_NAMESPACE

typedef struct{
    int linepos;
    int lineIndex;
}TextPosition;

typedef struct{
    string fileText;
    bool isXML;
}UndoRedoStackNode;


namespace Ui {
class XML_Editor;
}
QT_END_NAMESPACE

class XML_Editor : public QMainWindow
{
    Q_OBJECT

public:
    XML_Editor(QWidget *parent = nullptr);
    ~XML_Editor();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    string getXmlText();

    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::XML_Editor *ui;
};
#endif // XML_EDITOR_H
