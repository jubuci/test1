
#ifndef MYWIDGET_H

#define MYWIDGET_H
#include "draw.h"
#include <QWidget>

namespace Ui {
class MyWidget;
}
class MainWindow;
class MyWidget : public QWidget
{
    Q_OBJECT
//friend class DrawPointState;
public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    draw draw1;
    QPaintEvent *e;//如果去掉星号会变成error
//    DrawPointState one;
//  QPainter painter2;
    void DrawPoint(QPainter * painter,QWidget * widget);
    //friend void DrawPointState::paint(QPaintEvent *event,QWidget * widget);
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::MyWidget *ui;
signals:
//    void send_cwin();
//   friend void DrawPointState::paint(QPainter * painter,QWidget * widget);
};

#endif // MYWIDGET_H
