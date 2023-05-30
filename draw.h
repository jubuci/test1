#ifndef DRAW_H
#define DRAW_H

#include<QWidget>
#include<QGraphicsItem>
#include "QPainter"
#include "shape.h"
//#include "state.h"
class draw
{
public:
    QPainter painter;
    int GetShapeType();
    draw();
    void drawshape();
    void drawPoint(QPainter *painter);
    void drawCircle(QPainter* painter);
    Geometry* Create();
    Geometry* ReDraw();

    Geometry* geometry;
    Point m_curPoint;
    Circle m_curcircle;
    Rectangle m_currectangle;
    Sector m_cursector;

};
//virtual double Area() const { return 0; };
//virtual double Perimeter() const { return 0; };
//virtual bool IsContain(Point&pnt) const { return 0; };

class GraphicsBaseItem:public QGraphicsItem{
public:
//    friend bool Geometry::IsContain(Point &pnt)const;
//    //查看是否包含该点
//    ~GraphicsBaseItem(){};
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) override;
//    virtual bool SetSelected();
protected:
    QPoint m_mousePt;//鼠标当前位置
    bool m_selected;//是否被选择

};
class PointItem:public GraphicsBaseItem,Point{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget){
        painter->drawPoint(point.x,point.y);
    }
    bool IsContain(Point& pnt) const;
private:
    Point point;
};
class CricleItem:public GraphicsBaseItem,Circle{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget){
        painter->drawEllipse(circle.cx,circle.cy,circle.radius,circle.radius);
    }
private:
    Circle circle;
};

#endif // DRAW_H
