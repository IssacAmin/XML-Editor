#ifndef NETWORKWINDOW_H
#define NETWORKWINDOW_H

#include <QDialog>

namespace Ui {
class networkWindow;
}

class networkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit networkWindow(QWidget *parent = nullptr);
    ~networkWindow();

private:
    Ui::networkWindow *ui;
};

#endif // NETWORKWINDOW_H
