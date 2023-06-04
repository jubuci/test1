#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
    state=File;
}

void MyGraphicsView::SetState(states one){
    state=one;
}
void MyGraphicsView::mousePressEvent(QMouseEvent *e) {
    emit mousePressed(e);
    if (state == Edit) { // 事件继续传递该父类QGraphicsView
        QGraphicsView::mousePressEvent(e);
    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *e) {
    emit mouseMove(e);
    if (state == Edit) {
        QGraphicsView::mouseMoveEvent(e);
    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *e) {
    emit mouseReleased(e);
    if (state == Edit) {
        QGraphicsView::mouseReleaseEvent(e);
    }
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *e) {
    emit mouseDoubleClick(e);
    QGraphicsView::mouseDoubleClickEvent(e);
}
//void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
//{
//    QPoint point = e->pos();
//    emit mouseMovePoint(point);
//    QGraphicsView::mouseMoveEvent(event);
//}

//void MyGraphicsView::mousePressEvent(QMouseEvent *e)
//{
//    if(e->button() == Qt::LeftButton)
//    {
//        QPoint point = e->pos();
//        emit mouseClicked(point);
//    }
//    QGraphicsView::mousePressEvent(event);
//}



