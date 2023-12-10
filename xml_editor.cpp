#include "xml_editor.h"

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
        ui->widget1->setPlainText(text);
        file.close();

}

