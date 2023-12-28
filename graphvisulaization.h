#ifndef GRAPHVISULAIZATION_H
#define GRAPHVISULAIZATION_H

#include <QDialog>

namespace Ui {
class GraphVisulaization;
}

class GraphVisulaization : public QDialog
{
    Q_OBJECT

public:
    explicit GraphVisulaization(QWidget *parent = nullptr);
    ~GraphVisulaization();

private:
    Ui::GraphVisulaization *ui;
};

#endif // GRAPHVISULAIZATION_H
