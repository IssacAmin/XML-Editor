#include "graphvisulaization.h"
#include "ui_graphvisulaization.h"
#include <QPixmap>

GraphVisulaization::GraphVisulaization(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GraphVisulaization)
{
    ui->setupUi(this);
    QPixmap pic("C:\\XML-Editor\\Graph.png");
    ui->label->setPixmap(pic);
}

GraphVisulaization::~GraphVisulaization()
{
    delete ui;
}
