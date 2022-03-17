#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

private slots:
    void handleButton();

private:
    Ui::PlotWindow *ui;
};

#endif // PLOTWINDOW_H
