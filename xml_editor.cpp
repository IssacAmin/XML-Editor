#include "xml_editor.h"
#include "graphvisulaization.h"
#include "networkwindow.h"

//global vars
vector<string> fileContent;
vector<tag> errors;


//global stacks for redo and undo
stack<UndoRedoStackNode> undoStack;
stack<UndoRedoStackNode> RedoStack;

 bool isXML = false;
bool graphisBuilt = false;

XML_Editor::XML_Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XML_Editor)
{
    ui->setupUi(this);
    undoStack.push({"", true});

    isXML = false;

}

XML_Editor::~XML_Editor()
{
    delete ui;
}

string XML_Editor::getXmlText()
{
    return ui->widget->toPlainText().toStdString();
}


//open file button
void XML_Editor::on_pushButton_clicked()
{
    QString filePath = ui->lineEdit->text();
    if(filePath.toStdString().substr((filePath.size()-4),4).compare(".xml") == 0)
    {
        isXML = true;

    QFile file(filePath);\
        if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "file not found");
        }
        QTextStream in(&file);
        QString text = in.readAll();
        ui->widget->setPlainText(text);
        ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);


        undoStack.push({text.toStdString(), true});
        while(!RedoStack.empty())
            RedoStack.pop();
        file.close();
    }
    else
    {
        QMessageBox::warning(this, "title", "file is not XML format");
    }

}

//save file button
void XML_Editor::on_pushButton_3_clicked()
{
    QString filePath = ui->lineEdit->text();
    if(filePath == "")
    {
         QMessageBox::warning(this, "title", "File path is not Specified.");
    }
    else
    {
        if(filePath.toStdString().substr((filePath.size()-4),4) == ".xml")
        {
                isXML = true;

            QFile file(filePath);\
                if (!file.open(QFile::WriteOnly | QFile::Text)){
                QMessageBox::warning(this, "title", "file not found");
            }
            QTextStream out(&file);
            QString text = ui->widget->toPlainText();
            out<<text;
            file.flush();
            file.close();
        }
        else
        {
            QMessageBox::warning(this, "title", "file to save in is not XML format");
        }
    }
}

//Error checking button
void XML_Editor::on_pushButton_8_clicked()
{
    errors.clear();
    fileContent.clear();
    if(isXML)
    {
        string fileText = getXmlText();
        errors = ErrorDetection(fileText,fileContent);

        ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);

        //highlighting the errors in red
        QTextBlockFormat  fmt;
        fmt.setProperty(QTextFormat::FullWidthSelection, true);
        fmt.setBackground(Qt::red);
        for(int i = 0; i < (int) errors.size();i++)
        {

            QTextCursor cursor = ui->widget->textCursor();
            cursor.movePosition(QTextCursor::Start);
            cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, errors[i].line);
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.setBlockFormat(fmt);

            ui->widget->setTextCursor(cursor);

        }
        QString msg = "";
        for(int i = 0; i < (int) errors.size();i++)
        {
            msg += "error at line " + to_string(errors[i].line) + ": Missing" + (errors[i].type== OPENING?" OPENING TAG\n":" CLOSING TAG\n");
        }
        if(msg=="")
            QMessageBox::warning(this, "Errors", "No errors");
        else
            QMessageBox::warning(this, "Errors", msg);
    }
    else
    {
        QMessageBox::warning(this, "title", "text is not XML format");
    }

}

//Error Correction
void XML_Editor::on_pushButton_10_clicked()
{
    if(isXML)
    {
        errors.clear();
        fileContent.clear();
        string fileText = getXmlText();
        errors = ErrorDetection(fileText,fileContent);

       string xmlCorrectedText = errorCorrection(errors,fileContent);
       ui->widget->setPlainText(QString::fromStdString(xmlCorrectedText));
       ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);
       undoStack.push({xmlCorrectedText, true});
       while(!RedoStack.empty())
           RedoStack.pop();
    }
    else
    {
        QMessageBox::warning(this, "title", "text is not XML format");
    }

}



//Prettify button
void XML_Editor::on_pushButton_9_clicked()
{
    if(isXML)
    {
        string fileText = getXmlText();
        string prettyText = xmlindentor(fileText);
        ui->widget->setPlainText(QString::fromStdString(prettyText));
        ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);

        undoStack.push({prettyText, true});
        while(!RedoStack.empty())
            RedoStack.pop();
    }
    else
    {
        QMessageBox::warning(this, "title", "file is not XML format");
    }
}

//minify button
void XML_Editor::on_pushButton_5_clicked()
{
    if(isXML)
    {
        string fileText = getXmlText();
        string minifiedText = xmlminifier(fileText);
        ui->widget->setPlainText(QString::fromStdString(minifiedText));
        ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);

        undoStack.push({minifiedText, true});
        while(!RedoStack.empty())
            RedoStack.pop();
    }
    else
    {
          QMessageBox::warning(this, "title", "file is not XML format");
    }
}

//JSON Tranformation
void XML_Editor::on_pushButton_6_clicked()
{
    if(isXML)
    {
    string xmlText = getXmlText();
    string jsonText = xmlToJson(xmlText);
    ui->widget->setPlainText(QString::fromStdString(jsonText));
    ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);

    undoStack.push({jsonText, false});
    while(!RedoStack.empty())
        RedoStack.pop();
    isXML = false;
    }
    else
    {
        QMessageBox::warning(this, "title", "file is not XML format");
    }
}

//compress
void XML_Editor::on_pushButton_7_clicked()
{
    if(isXML)
    {
        string filePath = ui->lineEdit->text().toStdString();

        int found = 0;
        while(filePath.find('\\', found + 1) != string::npos)
        {
            found = filePath.find('\\', found + 1);
        }
        string newFilePath = filePath.substr(0,found + 1) + "Compressed.bin";
        string xmlText = getXmlText();
        compress(xmlText, newFilePath);
        ui->widget->setPlainText(QString::fromStdString(strBuffer));
        QMessageBox::warning(this, "title", "Compressed file generated at " + QString::fromStdString(newFilePath));


        undoStack.push({strBuffer, false});
        while(!RedoStack.empty())
            RedoStack.pop();
        isXML = false;
    }
    else
    {
        QMessageBox::warning(this, "title", "file is not XML format");
    }
}

//decompress
void XML_Editor::on_pushButton_4_clicked()
{

    string decompressedText =  file_decompress();
    ui->widget->setPlainText(QString::fromStdString(decompressedText));
    undoStack.push({strBuffer, true});
    while(!RedoStack.empty())
        RedoStack.pop();
    //xml format bool
    isXML =true;
}

//search button
void XML_Editor::on_pushButton_2_clicked()
{
     ui->widget->setPlainText(ui->widget->toPlainText());
    string text = ui->widget->toPlainText().toStdString();
    string targetText = ui->lineEdit_2->text().toStdString();
    vector<string>lines;
    stringstream ss(text);
    string line;
    vector<TextPosition> lineIndex;

    if (text.compare("") != 0)
    {
        while(std::getline(ss,line,'\n')){
            lines.push_back(line);
        }
    }
    else
        return;

    if(targetText.compare("") == 0)
    {
         QMessageBox::warning(this, "title", "Enter text to search for");
        return;
    }

    for(int i = 0;i < (int) lines.size(); i++)
    {
        size_t found = lines[i].find(targetText);
        if(found != string::npos)
        {
            lineIndex.push_back({(int)found, i});
        }
    }

    QTextCharFormat  fmt;
    fmt.setProperty(QTextFormat::FullWidthSelection, true);
    fmt.setBackground(Qt::green);
    ui->widget->setLineWrapMode(QPlainTextEdit::NoWrap);

    for(int i = 0; i < (int) lineIndex.size();i++)
    {

        QTextCursor cursor = ui->widget->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineIndex[i].lineIndex);
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, lineIndex[i].linepos);
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, (int)targetText.size());
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.setCharFormat(fmt);

        //ui->widget->setTextCursor(cursor);

    }

}



//undo button
void XML_Editor::on_pushButton_11_clicked()
{
    if(!undoStack.empty())
    {
        UndoRedoStackNode unDone = undoStack.top();
        undoStack.pop();
        isXML = undoStack.top().isXML;
        RedoStack.push(unDone);
        ui->widget->setPlainText(QString::fromStdString(undoStack.top().fileText));
    }
}

//Redo Button
void XML_Editor::on_pushButton_12_clicked()
{
    if(!RedoStack.empty())
    {
        UndoRedoStackNode reDone = RedoStack.top();
        RedoStack.pop();
        isXML = reDone.isXML;
        ui->widget->setPlainText(QString::fromStdString(reDone.fileText));
    }
}

//Graph button
void XML_Editor::on_pushButton_13_clicked()
{
    if(isXML)
    {
        string filePath = ui->lineEdit->text().toStdString();
        string text = XML_Editor::getXmlText();
        if(text != "")
        {
            string newFilePath = "C:\\XML-Editor\\Graph.png";

            adjList = build_Graph(text);
            createGraphVisualization(adjList,newFilePath);
            graphisBuilt =true;
            //opening the png in a pop up window
            GraphVisulaization graph;
            graph.setModal(true);
            graph.exec();
        }
        else
        {
            QMessageBox::warning(this, "title", "There is no text...");
        }
    }
    else
    {
        QMessageBox::warning(this, "title", "file is not XML format");
    }
}

//network analysis button
void XML_Editor::on_pushButton_14_clicked()
{
    if(isXML)
    {
        if(!graphisBuilt)
        {
            string text = XML_Editor::getXmlText();
            adjList = build_Graph(text);
        }

        networkWindow w;
        w.setModal(true);
        w.exec();
    }
    else
    {
        QMessageBox::warning(this, "title", "file is not XML format");
    }
}

