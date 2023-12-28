#ifndef NETWORKWINDOW_H
#define NETWORKWINDOW_H

#include <QDialog>
#include "xml_editor.h"
#include "Graph/graph.h"
namespace Ui {
class networkWindow;
}

class networkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit networkWindow(QWidget *parent = nullptr);
    ~networkWindow();

private slots:
    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::networkWindow *ui;
};

#endif // NETWORKWINDOW_H
