#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QWidget>
#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>

enum states{
    Edit,
    Draw,
    File
};
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget *parent = 0);
    void SetState(states one);

signals:
//    void mouseMovePoint(QPoint point);
//    void mouseClicked(QPoint point);
protected:
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
private:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

signals:
    void mouseMove(QMouseEvent *e); //鼠标移动
    void mousePressed(QMouseEvent *e); //鼠标单击
    void mouseReleased(QMouseEvent *e);
    void mouseDoubleClick(QMouseEvent *e); //双击事件

private:
    states state;
};

#endif // MYGRAPHICSVIEW_H

