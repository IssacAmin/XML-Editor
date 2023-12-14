#include "xml_editor.h"
#include <QTextCharFormat>


//global vars
vector<string> fileContent;

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

void XML_Editor::on_pushButton_clicked()
{
    QString filePath = ui->lineEdit->text();
    QFile file(filePath);\
        if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "file not found");
        }
        QTextStream in(&file);
        QString text = in.readAll();
        ui->widget->setPlainText(text);
        file.close();

}


void XML_Editor::on_pushButton_3_clicked()
{
    QString filePath = ui->lineEdit->text();
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


void XML_Editor::on_pushButton_8_clicked()
{
    QString filePath = ui->lineEdit->text();

    vector<tag> errors = ErrorDetection(filePath.toStdString(),fileContent);

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
        msg += "error at line " + to_string(errors[i].line) + ": Missing" + (errors[i].type== OPENING?" OPENING TAG\n":" CLSING TAG\n");
    }
    if(msg=="")
        QMessageBox::warning(this, "Errors", "No errors");
    else
        QMessageBox::warning(this, "Errors", msg);

}


void XML_Editor::on_pushButton_10_clicked()
{

}

