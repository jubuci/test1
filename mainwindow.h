#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "mywidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class DrawPointState;
friend class MyWidget;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyWidget state;
//    QPainter painter;
private slots:
    void on_actionopen_triggered();
    friend void MyWidget::DrawPoint(QPainter * painter,QWidget * widget);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
