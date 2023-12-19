#include "xml_editor.h"
#include <QTextCharFormat>


//global vars
vector<string> fileContent;
vector<tag> errors;
bool isXML = true;



XML_Editor::XML_Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XML_Editor)
{
    ui->setupUi(this);


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
        if(filePath.toStdString().substr((filePath.size()-5),4) == ".xml")
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

    if((int)fileContent.size() == 0)
    {
        string fileText = getXmlText();
        errors = ErrorDetection(fileText,fileContent);
    }

   string xmlCorrectedText = errorCorrection(errors,fileContent);
   ui->widget->setPlainText(QString::fromStdString(xmlCorrectedText));
   isXML = true;
}



//Prettify button
void XML_Editor::on_pushButton_9_clicked()
{
    if(isXML)
    {
        string fileText = getXmlText();
        string prettyText = xmlindentor(fileText);
        ui->widget->setPlainText(QString::fromStdString(prettyText));
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
    ui->widget->setPlainText(QString::fromStdString(xmlText));
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
        string xmlText = getXmlText();
        compress(xmlText,xmlText);
        ui->widget->setPlainText(QString::fromStdString(strBuffer));
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


    //xml format bool
    isXML =true;
}

//search button
void XML_Editor::on_pushButton_2_clicked()
{
    string text = ui->widget->toPlainText().toStdString();
    string targetText = ui->lineEdit_2->text().toStdString();
    vector<string>lines;
    stringstream ss(text);
    string line;
    vector<int> lineIndex;

    if (text != "")
    {
        while(std::getline(ss,line,'\n')){
            lines.push_back(line);
        }
    }
    else
    {
         QMessageBox::warning(this, "title", "Enter text to search for");
        return;
    }
    for(int i = 0;i < (int) lines.size(); i++)
    {
        lines[i].find(text);
        lineIndex.push_back(i);
    }

    QTextBlockFormat  fmt;
    fmt.setProperty(QTextFormat::FullWidthSelection, true);
    fmt.setBackground(Qt::green);
    for(int i = 0; i < (int) lineIndex.size();i++)
    {

        QTextCursor cursor = ui->widget->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineIndex[i]);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.setBlockFormat(fmt);

        ui->widget->setTextCursor(cursor);

    }

}


