#include "draw.h"

draw::draw()
{

}
void draw::drawshape(){
    this->painter.save();

}
void draw::drawPoint(QPainter *painter)
{

    painter->save();
    painter->drawPoint(10, 10);
    QPoint point(20, 20);
    painter->drawPoint(point);
    QPointF pointF(30, 30);
    painter->drawPoint(pointF);
    painter->restore();
}

//void mousePressEvent(QMouseEvent *event)
//{/*
//    if (currentState != NULL)
//    {
//        currentState->mousePressEvent(event);
//    }*/
//}
